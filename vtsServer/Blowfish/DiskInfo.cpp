
#include "DiskInfo.h"


std::string trim(std::string s)   
{  
    if(s.empty())   
    {  
        return s;  
    }  
    s.erase(0,s.find_first_not_of(" "));  
    s.erase(s.find_last_not_of(" ") + 1);  
    return s;  
}  

void change_byte_order(char *szString, unsigned short uscStrSize) 
{
	unsigned short i; 
	char temp;

	for (i = 0; i < uscStrSize; i+=2) 
	{ 
		temp = szString[i]; 
		szString[i] = szString[i+1]; 
		szString[i+1] = temp; 
	} 
}

void DiskInfo::AddSerialNumber(USHORT *pIdSector)
{
    WORD diskData[256];
    ::memcpy(diskData,pIdSector,256*sizeof(WORD));
    m_serialNumberVec.push_back(trim(ConvertToString(diskData, 10, 19)));
}

int DiskInfo::ReadPhysicalDriveInNTUsingSmart(void)
{
    int done = FALSE;
    int drive = 0;

    for(drive = 0; drive < MAX_IDE_DRIVES; drive++)
    {
        HANDLE hPhysicalDriveIOCTL = 0;

        //  Try to get a handle to PhysicalDrive IOCTL, report failure
        //  and exit if can't.

        char driveName [256];
        sprintf(driveName, "\\\\.\\PhysicalDrive%d", drive);

        //  Windows NT, Windows 2000, Windows Server 2003, Vista
        hPhysicalDriveIOCTL = CreateFileA(driveName,
            GENERIC_READ | GENERIC_WRITE, 
            FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE, 
            NULL, OPEN_EXISTING, 0, NULL);

        if(hPhysicalDriveIOCTL == INVALID_HANDLE_VALUE)
        {

        }
        else
        {
            GETVERSIONINPARAMS GetVersionParams;
            DWORD cbBytesReturned = 0;

            // Get the version, etc of PhysicalDrive IOCTL
            memset((void*) & GetVersionParams, 0, sizeof(GetVersionParams));

            if(  DeviceIoControl(hPhysicalDriveIOCTL, SMART_GET_VERSION,
                NULL, 
                0,
                &GetVersionParams, sizeof(GETVERSIONINPARAMS),
                &cbBytesReturned, NULL) )
            {         
                // Allocate the command buffer
                ULONG CommandSize = sizeof(SENDCMDINPARAMS) + IDENTIFY_BUFFER_SIZE;
                PSENDCMDINPARAMS Command =(PSENDCMDINPARAMS) malloc(CommandSize);
                // Retrieve the IDENTIFY data
                // Prepare the command
#define ID_CMD          0xEC            // Returns ID sector for ATA
                Command -> irDriveRegs.bCommandReg = ID_CMD;
                DWORD BytesReturned = 0;
                if( DeviceIoControl(hPhysicalDriveIOCTL, 
                    SMART_RCV_DRIVE_DATA, Command, sizeof(SENDCMDINPARAMS),
                    Command, CommandSize,
                    &BytesReturned, NULL) )

                {
                    // Print the IDENTIFY data
                    USHORT *pIdSector =(USHORT *)
                       (PIDENTIFY_DATA)((PSENDCMDOUTPARAMS) Command) -> bBuffer;


                    // AddIfNew(pIdSector);
                    AddSerialNumber(pIdSector);

                    done = TRUE;
                }
                // Done
                CloseHandle(hPhysicalDriveIOCTL);
                free(Command);
            }
        }
    }

    return done;
}

UINT DiskInfo::GetCount()
{
	return m_serialNumberVec.size();
}

int DiskInfo::ReadPhysicalDriveInNTWithAdminRights(void)
{
    int done = FALSE;
    int drive = 0;
    BYTE IdOutCmd [sizeof(SENDCMDOUTPARAMS) + IDENTIFY_BUFFER_SIZE - 1];
	SENDCMDINPARAMS  scip;
    for(drive = 0; drive < MAX_IDE_DRIVES; drive++)
    {
        HANDLE hPhysicalDriveIOCTL = 0;

        //  Try to get a handle to PhysicalDrive IOCTL, report failure
        //  and exit if can't.
        char driveName [256];

        sprintf(driveName, "\\\\.\\PhysicalDrive%d", drive);

        //  Windows NT, Windows 2000, must have admin rights
        hPhysicalDriveIOCTL = CreateFileA(driveName,
            GENERIC_READ | GENERIC_WRITE, 
            FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
            OPEN_EXISTING, 0, NULL);

        if(hPhysicalDriveIOCTL != INVALID_HANDLE_VALUE)
        {
            GETVERSIONOUTPARAMS VersionParams;
            DWORD               cbBytesReturned = 0;

            // Get the version, etc of PhysicalDrive IOCTL
            memset((void*) &VersionParams, 0, sizeof(VersionParams));

            if(  DeviceIoControl(hPhysicalDriveIOCTL, DFP_GET_VERSION,
                NULL, 
                0,
                &VersionParams,
                sizeof(VersionParams),
                &cbBytesReturned, NULL) )
            {         


                // If there is a IDE device at number "i" issue commands
                // to the device
                if(VersionParams.bIDEDeviceMap > 0)
                {
                    BYTE             bIDCmd = 0;   // IDE or ATAPI IDENTIFY cmd

                    // Now, get the ID sector for all IDE devices in the system.
                    // If the device is ATAPI use the IDE_ATAPI_IDENTIFY command,
                    // otherwise use the IDE_ATA_IDENTIFY command
                    bIDCmd =(VersionParams.bIDEDeviceMap >> drive & 0x10) ? \
IDE_ATAPI_IDENTIFY : IDE_ATA_IDENTIFY;

                    memset(&scip, 0, sizeof(scip));
                    memset(IdOutCmd, 0, sizeof(IdOutCmd));

                    if( DoIDENTIFY(hPhysicalDriveIOCTL, 
                        &scip, 
                       (PSENDCMDOUTPARAMS)&IdOutCmd, 
                       (BYTE) bIDCmd,
                       (BYTE) drive,
                        &cbBytesReturned))
                    {


                        USHORT *pIdSector =(USHORT *)
                           ((PSENDCMDOUTPARAMS) IdOutCmd) -> bBuffer;
                        // AddIfNew(pIdSector);	  
                        AddSerialNumber(pIdSector);
                        done = TRUE;
                    }
                }
				else if (VersionParams.fCapabilities&1)
				{
					//Identify the IDE drives 
					ZeroMemory(&scip,sizeof(scip)); 
					ZeroMemory(&IdOutCmd,sizeof(IdOutCmd)); 
					if (cbBytesReturned&1)
					{
						scip.irDriveRegs.bDriveHeadReg=0xb0; 
					}
					else
					{
						scip.irDriveRegs.bDriveHeadReg=0xa0;
					}
					if (VersionParams.fCapabilities&(16>>drive))
					{
						//We don't detect a ATAPI device. 
						CloseHandle(hPhysicalDriveIOCTL);
						continue;
					}
					else
					{
						scip.irDriveRegs.bCommandReg=0xec;
					}
					scip.bDriveNumber=drive;
					scip.irDriveRegs.bSectorCountReg=1;
					scip.irDriveRegs.bSectorNumberReg=1;
					scip.cBufferSize=512;

					if (!DeviceIoControl(hPhysicalDriveIOCTL,DFP_RECEIVE_DRIVE_DATA,&scip,sizeof(scip),&IdOutCmd,sizeof(IdOutCmd),&cbBytesReturned,0))
					{
						CloseHandle(hPhysicalDriveIOCTL);
						continue;
					}
					PIDSECTOR phdinfo = (PIDSECTOR)(IdOutCmd+sizeof(SENDCMDOUTPARAMS)-1);

					char serialNumber[21];
					memcpy(serialNumber,phdinfo->sSerialNumber,20);
					serialNumber[20] = 0;
					change_byte_order(serialNumber,20);
					m_serialNumberVec.push_back(trim(serialNumber));
					done = TRUE;
				}
            }

            CloseHandle(hPhysicalDriveIOCTL);
        }
    }

    return done;
}


//  Required to ensure correct PhysicalDrive IOCTL structure setup
#pragma pack(4)

#ifndef VC90

//IOCTL_STORAGE_QUERY_PROPERTY

//Input Buffer:
//     a STORAGE_PROPERTY_QUERY structure which describes what type of query
//     is being done, what property is being queried for, and any additional
//     parameters which a particular property query requires.

// Output Buffer:
//     Contains a buffer to place the results of the query into.  Since all
//     property descriptors can be cast into a STORAGE_DESCRIPTOR_HEADER,
//     the IOCTL can be called once with a small buffer then again using
//     a buffer as large as the header reports is necessary.

//Types of queries


typedef enum _STORAGE_QUERY_TYPE {
    PropertyStandardQuery = 0,          // Retrieves the descriptor
    PropertyExistsQuery,                // Used to test whether the descriptor is supported
    PropertyMaskQuery,                  // Used to retrieve a mask of writeable fields in the descriptor
    PropertyQueryMaxDefined     // use to validate the value
} STORAGE_QUERY_TYPE, *PSTORAGE_QUERY_TYPE;


//define some initial property id's


typedef enum _STORAGE_PROPERTY_ID {
    StorageDeviceProperty = 0,
    StorageAdapterProperty
} STORAGE_PROPERTY_ID, *PSTORAGE_PROPERTY_ID;


//Query structure - additional parameters for specific queries can follow
//the header


typedef struct _STORAGE_PROPERTY_QUERY {

    //
    // ID of the property being retrieved
    //

    STORAGE_PROPERTY_ID PropertyId;

    //
    // Flags indicating the type of query being performed
    //

    STORAGE_QUERY_TYPE QueryType;

    //
    // Space for additional parameters if necessary
    //

    UCHAR AdditionalParameters[1];

} STORAGE_PROPERTY_QUERY, *PSTORAGE_PROPERTY_QUERY;
#endif

#define IOCTL_STORAGE_QUERY_PROPERTY   CTL_CODE(IOCTL_STORAGE_BASE, 0x0500, METHOD_BUFFERED, FILE_ANY_ACCESS)


//
// Device property descriptor - this is really just a rehash of the inquiry
// data retrieved from a scsi device
//
// This may only be retrieved from a target device.  Sending this to the bus
// will result in an error
//
#ifndef VC90
typedef struct _STORAGE_DEVICE_DESCRIPTOR {

    //
    // Sizeof(STORAGE_DEVICE_DESCRIPTOR)
    //

    ULONG Version;

    //
    // Total size of the descriptor, including the space for additional
    // data and id strings
    //

    ULONG Size;

    //
    // The SCSI-2 device type
    //

    UCHAR DeviceType;

    //
    // The SCSI-2 device type modifier(if any) - this may be zero
    //

    UCHAR DeviceTypeModifier;

    //
    // Flag indicating whether the device's media(if any) is removable.  This
    // field should be ignored for media-less devices
    //

    BOOLEAN RemovableMedia;

    //
    // Flag indicating whether the device can support mulitple outstanding
    // commands.  The actual synchronization in this case is the responsibility
    // of the port driver.
    //

    BOOLEAN CommandQueueing;

    //
    // Byte offset to the zero-terminated ascii string containing the device's
    // vendor id string.  For devices with no such ID this will be zero
    //

    ULONG VendorIdOffset;

    //
    // Byte offset to the zero-terminated ascii string containing the device's
    // product id string.  For devices with no such ID this will be zero
    //

    ULONG ProductIdOffset;

    //
    // Byte offset to the zero-terminated ascii string containing the device's
    // product revision string.  For devices with no such string this will be
    // zero
    //

    ULONG ProductRevisionOffset;

    //
    // Byte offset to the zero-terminated ascii string containing the device's
    // serial number.  For devices with no serial number this will be zero
    //

    ULONG SerialNumberOffset;

    //
    // Contains the bus type(as defined above) of the device.  It should be
    // used to interpret the raw device properties at the end of this structure
    //(if any)
    //

    STORAGE_BUS_TYPE BusType;

    //
    // The number of bytes of bus-specific data which have been appended to
    // this descriptor
    //

    ULONG RawPropertiesLength;

    //
    // Place holder for the first byte of the bus specific property data
    //

    UCHAR RawDeviceProperties[1];

} STORAGE_DEVICE_DESCRIPTOR, *PSTORAGE_DEVICE_DESCRIPTOR;
#endif


//  function to decode the serial numbers of IDE hard drives
//  using the IOCTL_STORAGE_QUERY_PROPERTY command 
char * DiskInfo::flipAndCodeBytes(char * str)
{
    static char flipped [1000];
    int num = strlen(str);
    strcpy(flipped, "");
    for(int i = 0; i < num; i += 4)
    {
        for(int j = 1; j >= 0; j--)
        {
            int sum = 0;
            for(int k = 0; k < 2; k++)
            {
                sum *= 16;
                switch(str [i + j * 2 + k])
                {
                case '0': sum += 0; break;
                case '1': sum += 1; break;
                case '2': sum += 2; break;
                case '3': sum += 3; break;
                case '4': sum += 4; break;
                case '5': sum += 5; break;
                case '6': sum += 6; break;
                case '7': sum += 7; break;
                case '8': sum += 8; break;
                case '9': sum += 9; break;
                case 'a': sum += 10; break;
                case 'b': sum += 11; break;
                case 'c': sum += 12; break;
                case 'd': sum += 13; break;
                case 'e': sum += 14; break;
                case 'f': sum += 15; break;
                }
            }
            if(sum > 0) 
            {
                char sub [2];
                sub [0] =(char) sum;
                sub [1] = 0;
                strcat(flipped, sub);
            }
        }
    }

    return flipped;
}


typedef struct _MEDIA_SERAL_NUMBER_DATA {
    ULONG  SerialNumberLength; 
    ULONG  Result;
    ULONG  Reserved[2];
    UCHAR  SerialNumberData[1];
} MEDIA_SERIAL_NUMBER_DATA, *PMEDIA_SERIAL_NUMBER_DATA;


int DiskInfo::ReadPhysicalDriveInNTWithZeroRights(void)
{
    int done = FALSE;
    int drive = 0;

    for(drive = 0; drive < MAX_IDE_DRIVES; drive++)
    {
        HANDLE hPhysicalDriveIOCTL = 0;

        //  Try to get a handle to PhysicalDrive IOCTL, report failure
        //  and exit if can't.
        char driveName [256];

        sprintf(driveName, "\\\\.\\PhysicalDrive%d", drive);

        //  Windows NT, Windows 2000, Windows XP - admin rights not required
        hPhysicalDriveIOCTL = CreateFileA(driveName, 0,
            FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
            OPEN_EXISTING, 0, NULL);


        if(hPhysicalDriveIOCTL != INVALID_HANDLE_VALUE)
        {
            STORAGE_PROPERTY_QUERY query;
            DWORD cbBytesReturned = 0;
            char buffer [1024];

            memset((void *) & query, 0, sizeof(query));
            query.PropertyId = StorageDeviceProperty;
            query.QueryType = PropertyStandardQuery;

            memset(buffer, 0, sizeof(buffer));

            if( DeviceIoControl(hPhysicalDriveIOCTL, IOCTL_STORAGE_QUERY_PROPERTY,
                & query,
                sizeof(query),
                & buffer,
                sizeof(buffer),
                & cbBytesReturned, NULL) )
            {         
                STORAGE_DEVICE_DESCRIPTOR * descrip =(STORAGE_DEVICE_DESCRIPTOR *) & buffer;
                char serialNumber[512];
                /*
                strcpy(serialNumber, 
                flipAndCodeBytes( & buffer [descrip -> SerialNumberOffset]));
                */
                strcpy(serialNumber, &buffer[descrip -> SerialNumberOffset]);
				// change_byte_order(serialNumber, strlen(serialNumber));

                /*
                int isAlnumAndSpace = TRUE;
                int isAllSpace = TRUE;
                int length=strlen(serialNumber);
                for(int i=0;i<length;i++){
                    if(!isalnum(serialNumber[i]) && serialNumber[i] != ' '){
                        isAlnumAndSpace=FALSE;
                        break;
                    }

                    if(isAllSpace && serialNumber[i] != ' '){
                        isAllSpace=FALSE;
                    }
                }
                */
                //Ӳ�̱��Ϊ��ĸ�����ֺͿո񣬵����Ǵ��ո�
                /*
                if(isAlnumAndSpace && !isAllSpace)
                {
                    m_serialNumberVec.push_back(trim(serialNumber));
                }
                */
                m_serialNumberVec.push_back(trim(serialNumber));

                done=TRUE;
            }

            CloseHandle(hPhysicalDriveIOCTL);
        }
    }
    return done;
}


// DoIDENTIFY
// FUNCTION: Send an IDENTIFY command to the drive
// bDriveNum = 0-3
// bIDCmd = IDE_ATA_IDENTIFY or IDE_ATAPI_IDENTIFY
BOOL DiskInfo::DoIDENTIFY(HANDLE hPhysicalDriveIOCTL, PSENDCMDINPARAMS pSCIP,
    PSENDCMDOUTPARAMS pSCOP, BYTE bIDCmd, BYTE bDriveNum,
    PDWORD lpcbBytesReturned)
{
    // Set up data structures for IDENTIFY command.
    pSCIP -> cBufferSize = IDENTIFY_BUFFER_SIZE;
    pSCIP -> irDriveRegs.bFeaturesReg = 0;
    pSCIP -> irDriveRegs.bSectorCountReg = 1;
    pSCIP -> irDriveRegs.bSectorNumberReg = 1;
    pSCIP -> irDriveRegs.bCylLowReg = 0;
    pSCIP -> irDriveRegs.bCylHighReg = 0;

    // Compute the drive number.
    pSCIP -> irDriveRegs.bDriveHeadReg = 0xA0 |((bDriveNum & 1) << 4);

    // The command can either be IDE identify or ATAPI identify.
    pSCIP -> irDriveRegs.bCommandReg = bIDCmd;
    pSCIP -> bDriveNumber = bDriveNum;
    pSCIP -> cBufferSize = IDENTIFY_BUFFER_SIZE;

    return( DeviceIoControl(hPhysicalDriveIOCTL, DFP_RECEIVE_DRIVE_DATA,
       (LPVOID) pSCIP,
        sizeof(SENDCMDINPARAMS) - 1,
       (LPVOID) pSCOP,
        sizeof(SENDCMDOUTPARAMS) + IDENTIFY_BUFFER_SIZE - 1,
        lpcbBytesReturned, NULL) );
}


//  ---------------------------------------------------

//(* Output Bbuffer for the VxD(rt_IdeDinfo record) *)
typedef struct _rt_IdeDInfo_
{
    BYTE IDEExists[4];
    BYTE DiskExists[8];
    WORD DisksRawInfo[8*256];
} rt_IdeDInfo, *pt_IdeDInfo;


//(* IdeDinfo "data fields" *)
typedef struct _rt_DiskInfo_
{
    BOOL DiskExists;
    BOOL ATAdevice;
    BOOL RemovableDevice;
    WORD TotLogCyl;
    WORD TotLogHeads;
    WORD TotLogSPT;
    char SerialNumber[20];
    char FirmwareRevision[8];
    char ModelNumber[40];
    WORD CurLogCyl;
    WORD CurLogHeads;
    WORD CurLogSPT;
} rt_DiskInfo;


#define  m_cVxDFunctionIdesDInfo  1


//  ---------------------------------------------------


int DiskInfo::ReadDrivePortsInWin9X(void)
{
    int done = FALSE;

    HANDLE VxDHandle = 0;
    pt_IdeDInfo pOutBufVxD = 0;
    DWORD lpBytesReturned = 0;

    //  set the thread priority high so that we get exclusive access to the disk
    BOOL status =
        // SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
        SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
    // SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);

    // 1. Make an output buffer for the VxD
    rt_IdeDInfo info;
    pOutBufVxD = &info;

    // *****************
    // KLUDGE WARNING!!!
    // HAVE to zero out the buffer space for the IDE information!
    // If this is NOT done then garbage could be in the memory
    // locations indicating if a disk exists or not.
    ZeroMemory(&info, sizeof(info));

    // 1. Try to load the VxD
    //  must use the short file name path to open a VXD file
    //char StartupDirectory [2048];
    //char shortFileNamePath [2048];
    //char *p = NULL;
    //char vxd [2048];
    //  get the directory that the exe was started from
    //GetModuleFileName(hInst,(LPSTR) StartupDirectory, sizeof(StartupDirectory));
    //  cut the exe name from string
    //p = &(StartupDirectory [strlen(StartupDirectory) - 1]);
    //while(p >= StartupDirectory && *p && '\\' != *p) p--;
    //*p = '\0';   
    //GetShortPathName(StartupDirectory, shortFileNamePath, 2048);
    //sprintf(vxd, "\\\\.\\%s\\IDE21201.VXD", shortFileNamePath);
    //VxDHandle = CreateFile(vxd, 0, 0, 0,
    //               0, FILE_FLAG_DELETE_ON_CLOSE, 0);   
    VxDHandle = CreateFileA("\\\\.\\IDE21201.VXD", 0, 0, 0,
        0, FILE_FLAG_DELETE_ON_CLOSE, 0);

    if(VxDHandle != INVALID_HANDLE_VALUE)
    {
        // 2. Run VxD function
        DeviceIoControl(VxDHandle, m_cVxDFunctionIdesDInfo,
            0, 0, pOutBufVxD, sizeof(pt_IdeDInfo), &lpBytesReturned, 0);

        // 3. Unload VxD
        CloseHandle(VxDHandle);
    }
    else
        //::MessageBox(NULL, L"ERROR: Could not open IDE21201.VXD file", 
        //	TITLE, MB_ICONSTOP);
        return FALSE;


    // 4. Translate and store data
    unsigned long int i = 0;
    for(i=0; i<8; i++)
    {
        if((pOutBufVxD->DiskExists[i]) &&(pOutBufVxD->IDEExists[i/2]))
        {

            WORD diskData[256];
            for(int j = 0; j < 256; j++) 
                diskData [j] = pOutBufVxD -> DisksRawInfo [i * 256 + j];

            m_serialNumberVec.push_back(trim(ConvertToString(diskData, 10, 19)));

            /*
            WORD* diskData = new WORD[256];
            for(int j = 0; j < 256; j++) 
                diskData [j] = pOutBufVxD -> DisksRawInfo [i * 256 + j];


            // process the information for this buffer
            BOOL bAdd = TRUE;
            for(UINT j =0; j< m_list.size();j++)
            {
                if(memcmp(diskData,m_list[j],256 * sizeof(WORD)) == 0)
                {
                    bAdd = false;
                    break;
                }
            }
            if(bAdd)
                m_list.push_back(diskData);
            else
                delete diskData;
            */

            done = TRUE;
        }
    }

    //  reset the thread priority back to normal
    SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS);

    return done;
}


#define  SENDIDLENGTH  sizeof(SENDCMDOUTPARAMS) + IDENTIFY_BUFFER_SIZE


int DiskInfo::ReadIdeDriveAsScsiDriveInNT(void)
{
    int done = FALSE;
    int controller = 0;

    for(controller = 0; controller < 16; controller++)
    {
        HANDLE hScsiDriveIOCTL = 0;
        char   driveName [256];

        //  Try to get a handle to PhysicalDrive IOCTL, report failure
        //  and exit if can't.
        sprintf(driveName, "\\\\.\\Scsi%d:", controller);

        //  Windows NT, Windows 2000, any rights should do
        hScsiDriveIOCTL = CreateFileA(driveName,
            GENERIC_READ | GENERIC_WRITE, 
            FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
            OPEN_EXISTING, 0, NULL);


        if(hScsiDriveIOCTL != INVALID_HANDLE_VALUE)
        {
            int drive = 0;

            for(drive = 0; drive < 2; drive++)
            {
                char buffer [sizeof(SRB_IO_CONTROL) + SENDIDLENGTH];
                SRB_IO_CONTROL *p =(SRB_IO_CONTROL *) buffer;
                SENDCMDINPARAMS *pin =
                   (SENDCMDINPARAMS *)(buffer + sizeof(SRB_IO_CONTROL));
                DWORD dummy;

                memset(buffer, 0, sizeof(buffer));
                p -> HeaderLength = sizeof(SRB_IO_CONTROL);
                p -> Timeout = 10000;
                p -> Length = SENDIDLENGTH;
                p -> ControlCode = IOCTL_SCSI_MINIPORT_IDENTIFY;
                strncpy((char *) p -> Signature, "SCSIDISK", 8);

                pin -> irDriveRegs.bCommandReg = IDE_ATA_IDENTIFY;
                pin -> bDriveNumber = drive;

                if(DeviceIoControl(hScsiDriveIOCTL, IOCTL_SCSI_MINIPORT, 
                    buffer,
                    sizeof(SRB_IO_CONTROL) +
                    sizeof(SENDCMDINPARAMS) - 1,
                    buffer,
                    sizeof(SRB_IO_CONTROL) + SENDIDLENGTH,
                    &dummy, NULL))
                {
                    SENDCMDOUTPARAMS *pOut =
                       (SENDCMDOUTPARAMS *)(buffer + sizeof(SRB_IO_CONTROL));
                    IDSECTOR *pId =(IDSECTOR *)(pOut -> bBuffer);
                    if(pId -> sModelNumber [0])
                    {

                        USHORT *pIdSector =(USHORT *) pId;
                        // AddIfNew(pIdSector);	
                        AddSerialNumber(pIdSector);
                        //BOOL bAdd = TRUE;
                        //  for(UINT i =0; i< m_list.size();i++)
                        //  {
                        //   if(memcmp(pIdSector,m_list[i],256 * sizeof(WORD)) == 0)
                        //   {
                        //	   bAdd = false;
                        //	   break;
                        //   }
                        //  }
                        //  if(bAdd)
                        //  {
                        //    WORD* diskdata = new WORD[256];
                        //	 ::memcpy(diskdata,pIdSector,256*sizeof(WORD));
                        //	 m_list.push_back(diskdata);
                        //  }

                        done = TRUE;
                    }
                }
            }
            CloseHandle(hScsiDriveIOCTL);
        }
    }

    return done;
}


const char* DiskInfo::getSerialNumber(UINT drive)
{
    return m_serialNumberVec[drive].c_str();
}

char * DiskInfo::ConvertToString(WORD diskData [256], int firstIndex, int lastIndex)
{
    static char string [1024];
    int index = 0;
    int position = 0;

    //  each integer has two characters stored in it backwards
    for(index = firstIndex; index <= lastIndex; index++)
    {
        //  get high byte for 1st character
        string [position] =(char)(diskData [index] / 256);
        position++;

        //  get low byte for 2nd character
        string [position] =(char)(diskData [index] % 256);
        position++;
    }

    //  end the string 
    string [position] = '\0';

    //  cut off the trailing blanks
    for(index = position - 1; index > 0 && ' ' == string [index]; index--)
        string [index] = '\0';

    return string;
}

DiskInfo::DiskInfo(void)
{
    //m_DriveCount = 0;
}

DiskInfo::~DiskInfo(void)
{
}


int DiskInfo::LoadDiskInfo()
{
    int done = FALSE;
    __int64 id = 0;
    OSVERSIONINFO version;
    memset(&version, 0, sizeof(version));
    version.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&version);

    m_serialNumberVec.clear();

    if(version.dwPlatformId == VER_PLATFORM_WIN32_NT)
    {
        //  this works under WinNT4 or Win2K if you have admin rights
        done = ReadPhysicalDriveInNTWithAdminRights();
        if(!done)
        {
            //  this should work in WinNT or Win2K if previous did not work
            //  this is kind of a backdoor via the SCSI mini port driver into
            //     the IDE drives
            done = ReadIdeDriveAsScsiDriveInNT();
        }

        if(!done)
        {
            //this works under WinNT4 or Win2K or WinXP if you have any rights
            done = ReadPhysicalDriveInNTWithZeroRights();
        }

        if(!done)
        {
            done = ReadPhysicalDriveInNTUsingSmart();
        }
    }
    else
    {
        //  this works under Win9X and calls a VXD
        int attempt = 0;

        //  try this up to 10 times to get a hard drive serial number
        for(attempt = 0; attempt < 10 && !done ; attempt++)
            done = ReadDrivePortsInWin9X();
    }

    return m_serialNumberVec.size();
}
