/*
Copyright (C) 1996-1997 Id Software, Inc.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

    $Id: common.h,v 1.32 2006-12-30 21:03:45 cokeman1982 Exp $
*/
// common.h  -- general definitions

#ifndef __COMMON_H__
#define __COMMON_H__

//============================================================================

// include frequently used headers

#include "q_shared.h"
#include "zone.h"
#include "cvar.h"
#include "cmd.h"
#include "net.h"
#include "protocol.h"

#ifdef WITH_ZIP
#include "unzip.h"
#endif

//============================================================================

// per-level limits
#define	CL_MAX_EDICTS		768		// FIXME: ouch! ouch! ouch!
#define	SV_MAX_EDICTS		1024	// FIXME: ouch! ouch! ouch!
#define	MAX_LIGHTSTYLES		64
#define	MAX_MODELS			256		// these are sent over the net as bytes
#define MAX_VWEP_MODELS 	32		// could be increased to 256
#define	MAX_SOUNDS			256		// so they cannot be blindly increased

#define	SAVEGAME_COMMENT_LENGTH	39

//============================================================================

// stats are integers communicated to the client by the server
#define	MAX_CL_STATS		32
#define	STAT_HEALTH			0
//define STAT_FRAGS			1
#define	STAT_WEAPON			2
#define	STAT_AMMO			3
#define	STAT_ARMOR			4
//define STAT_WEAPONFRAME	5
#define	STAT_SHELLS			6
#define	STAT_NAILS			7
#define	STAT_ROCKETS		8
#define	STAT_CELLS			9
#define	STAT_ACTIVEWEAPON	10
#define	STAT_TOTALSECRETS	11
#define	STAT_TOTALMONSTERS	12
#define	STAT_SECRETS		13		// bumped on client side by svc_foundsecret
#define	STAT_MONSTERS		14		// bumped by svc_killedmonster
#define	STAT_ITEMS			15
#define STAT_VIEWHEIGHT		16		// Z_EXT_VIEWHEIGHT protocol extension
#define STAT_TIME			17		// Z_EXT_TIME extension

// item flags
#define	IT_SHOTGUN			1
#define	IT_SUPER_SHOTGUN	2
#define	IT_NAILGUN			4
#define	IT_SUPER_NAILGUN	8
#define	IT_GRENADE_LAUNCHER	16
#define	IT_ROCKET_LAUNCHER	32
#define	IT_LIGHTNING		64
#define	IT_SUPER_LIGHTNING	128

#define	IT_SHELLS			256
#define	IT_NAILS			512
#define	IT_ROCKETS			1024
#define	IT_CELLS			2048

#define	IT_AXE				4096

#define	IT_ARMOR1			8192
#define	IT_ARMOR2			16384
#define	IT_ARMOR3			32768

#define	IT_SUPERHEALTH		65536

#define	IT_KEY1				131072
#define	IT_KEY2				262144

#define	IT_INVISIBILITY		524288

#define	IT_INVULNERABILITY	1048576
#define	IT_SUIT				2097152
#define	IT_QUAD				4194304

#define	IT_SIGIL1			(1<<28)

#define	IT_SIGIL2			(1<<29)
#define	IT_SIGIL3			(1<<30)
#define	IT_SIGIL4			(1<<31)

// print flags
#define	PRINT_LOW			0		// pickup messages
#define	PRINT_MEDIUM		1		// death messages
#define	PRINT_HIGH			2		// critical messages
#define	PRINT_CHAT			3		// chat messages

// game types sent by serverinfo
// these determine which intermission screen plays
#define	GAME_COOP			0
#define	GAME_DEATHMATCH		1

#define	MAX_INFO_KEY	64
#define	MAX_INFO_STRING	384
#define	MAX_SERVERINFO_STRING	512
#define	MAX_LOCALINFO_STRING	32768

//============================================================================

#define MAX_COM_TOKEN	1024

extern	char	com_token[MAX_COM_TOKEN];
extern	qbool	com_eof;

char *COM_Parse (char *data);

extern	int		com_argc;
extern	char	**com_argv;

void COM_InitArgv (int argc, char **argv);
int COM_Argc (void);
char *COM_Argv (int arg); // range and null checked
void COM_ClearArgv (int arg);
int COM_CheckParm (char *parm);
void COM_AddParm (char *parm);

void COM_Init (void);

char *COM_SkipPath (char *pathname);
char *COM_FitPath(char *dest, int destination_size, char *src, int size_to_fit);
char *COM_FileExtension (char *in);
void COM_StripExtension (char *in, char *out);
void COM_FileBase (char *in, char *out);
void COM_DefaultExtension (char *path, char *extension);
void COM_ForceExtension (char *path, char *extension);
int COM_FileLength (FILE *f);
int COM_FileOpenRead (char *path, FILE **hndl);
int COM_GetTempDir(char *buf, int bufsize);
int COM_GetUniqueTempFilename (char *path, char *filename, int filename_size, qbool verify_exists);

void COM_StoreOriginalCmdline(int argc, char **argv);

extern char * SYSINFO_GetString(void);

char *va(char *format, ...);
// does a varargs printf into a temp buffer

//============================================================================

extern int fs_filesize;
extern qbool com_filefrompak;
extern char *com_filesearchpath;
extern char	fs_netpath[MAX_OSPATH];
struct cache_user_s;

extern char	com_gamedir[MAX_OSPATH];
extern char	com_basedir[MAX_OSPATH];
extern char	com_gamedirfile[MAX_QPATH];

// QW262 -->
#ifndef SERVERONLY
#define UserdirSet (userdirfile[0] != '\0')
extern	char	userdirfile[MAX_OSPATH];
extern	char	com_userdir[MAX_OSPATH];
void COM_SetUserDirectory (char *dir, char *type);
#endif
// <-- QW262

extern qbool file_from_pak;		// set if file came from a pak file
extern qbool file_from_gamedir;	// set if file came from a gamedir (and gamedir wasn't id1/qw)

void FS_InitFilesystem (void);
void FS_SetGamedir (char *dir);
int FS_FOpenFile (char *filename, FILE **file);
byte *FS_LoadStackFile (char *path, void *buffer, int bufsize);
byte *FS_LoadTempFile (char *path);
byte *FS_LoadHunkFile (char *path);
void FS_LoadCacheFile (char *path, struct cache_user_s *cu);

qbool COM_WriteFile (char *filename, void *data, int len);
void COM_CreatePath (char *path);
int COM_FCreateFile (char *filename, FILE **file, char *path, char *mode);


char *Info_ValueForKey (char *s, char *key);
void Info_RemoveKey (char *s, char *key);
void Info_RemovePrefixedKeys (char *start, char prefix);
void Info_SetValueForKey (char *s, char *key, char *value, int maxsize);
void Info_SetValueForStarKey (char *s, char *key, char *value, int maxsize);
void Info_Print (char *s);

unsigned Com_BlockChecksum (void *buffer, int length);
void Com_BlockFullChecksum (void *buffer, int len, unsigned char *outbuf);
byte COM_BlockSequenceCRCByte (byte *base, int length, int sequence);

//============================================================================

void Com_BeginRedirect (void (*RedirectedPrint) (char *));
void Com_EndRedirect (void);
void Com_Printf (char *fmt, ...);
void Com_DPrintf (char *fmt, ...);
#define PRINT_OK	1
#define PRINT_INFO	2
#define PRINT_FAIL	4
void Com_Printf_State(int state, char *fmt, ...);

extern unsigned	Print_flags[16];
extern int	Print_current;

#define		PR_SKIP		1
#define		PR_LOG_SKIP	2
#define		PR_TR_SKIP	4
#define		PR_IS_CHAT	8

//============================================================================

struct usercmd_s;

extern struct usercmd_s nullcmd;

void MSG_WriteChar (sizebuf_t *sb, int c);
void MSG_WriteByte (sizebuf_t *sb, int c);
void MSG_WriteShort (sizebuf_t *sb, int c);
void MSG_WriteLong (sizebuf_t *sb, int c);
void MSG_WriteFloat (sizebuf_t *sb, float f);
void MSG_WriteString (sizebuf_t *sb, char *s);
void MSG_WriteUnterminatedString (sizebuf_t *sb, char *s);
void MSG_WriteCoord (sizebuf_t *sb, float f);
void MSG_WriteAngle (sizebuf_t *sb, float f);
void MSG_WriteAngle16 (sizebuf_t *sb, float f);
void MSG_WriteDeltaUsercmd (sizebuf_t *sb, struct usercmd_s *from, struct usercmd_s *cmd);
void MSG_WriteDeltaEntity  (entity_state_t *from, entity_state_t *to, sizebuf_t *msg, qbool force);
void MSG_EmitPacketEntities (packet_entities_t *from, int delta_sequence, packet_entities_t *to,
                             sizebuf_t *msg, entity_state_t *(*GetBaseline)(int number));

extern	int	msg_readcount;
extern	qbool	msg_badread; // set if a read goes beyond end of message

void MSG_BeginReading (void);
int MSG_GetReadCount(void);
int MSG_ReadChar (void);
int MSG_ReadByte (void);
int MSG_ReadShort (void);
int MSG_ReadLong (void);
float MSG_ReadFloat (void);
char *MSG_ReadString (void);
char *MSG_ReadStringLine (void);

float MSG_ReadCoord (void);
float MSG_ReadAngle (void);
float MSG_ReadAngle16 (void);
void MSG_ReadDeltaUsercmd (struct usercmd_s *from, struct usercmd_s *cmd, int protoversion);

//============================================================================

#ifdef SERVERONLY
#define dedicated 1
#elif CLIENTONLY
#define dedicated 0
#else
extern qbool	dedicated;
#endif

extern cvar_t	developer;
extern cvar_t	mapname;

extern qbool	com_serveractive; // true if sv.state != ss_dead
extern int	CL_ClientState (); // returns cls.state

extern double	curtime; // not bounded or scaled, shared by local client and server

// host
extern qbool host_initialized;
extern int host_memsize;

void Host_Init (int argc, char **argv, int default_memsize);
void Host_ClearMemory ();
void Host_Shutdown (void);
void Host_Frame (double time);
void Host_Abort (void);	 // longjmp() to Host_Frame
void Host_EndGame (void); // kill local client and server
void Host_Error (char *error, ...);
void Host_Quit (void);

void CL_Init (void);
void CL_Shutdown (void);
void CL_Frame (double time);
void CL_Disconnect ();
void CL_BeginLocalConnection (void);
void CL_UpdateCaption (void);
void Con_Init (void);
void Con_Print (char *txt);

void SV_Init (void);
void SV_Shutdown (char *finalmsg);
void SV_Frame (double time);

int isspace2(int c);

#ifdef WITH_ZIP
qbool COM_ZipIsArchive (char *zip_path);

int COM_ZipBreakupArchivePath (char *archive_extension,			// The extension of the archive type we're looking fore "zip" for example.
							   char *path,						// The path that should be broken up into parts.
							   char *archive_path,				// The buffer that should contain the archive path after the breakup.
							   int archive_path_size,			// The size of the archive path buffer.
							   char *inzip_path,				// The buffer that should contain the inzip path after the breakup.
							   int inzip_path_size);			// The size of the inzip path buffer.

unzFile COM_ZipUnpackOpenFile (const char *zip_path);

int COM_ZipUnpackCloseFile (unzFile zip_file);

int COM_ZipUnpack (unzFile zip_file, 
				   char *destination_path, 
				   qbool case_sensitive, 
				   qbool keep_path, 
				   qbool overwrite, 
				   const char *password);

int COM_ZipUnpackOneFile (unzFile zip_file,				// The zip file opened with COM_ZipUnpackOpenFile(..)
						  const char *filename_inzip,	// The name of the file to unpack inside the zip.
						  const char *destination_path, // The destination path where to extract the file to.
						  qbool case_sensitive,			// Should we look for the filename case sensitivly?
						  qbool keep_path,				// Should the path inside the zip be preserved when unpacking?
						  qbool overwrite,				// Overwrite any existing file with the same name when unpacking?
						  const char *password);		// The password to use when extracting the file.

int COM_ZipUnpackOneFileToTemp (unzFile zip_file, 
						  const char *filename_inzip,
						  qbool case_sensitive, 
						  qbool keep_path,
						  qbool overwrite,
						  const char *password,
						  char *unpack_path,			// The path where the file was unpacked.
						  int unpack_path_size,			// The size of the buffer for "unpack_path", MAX_PATH is a goode idea.
						  char *append_extension);		// If any extension should be appended to the unpacked filename.

int COM_ZipUnpackCurrentFile (unzFile zip_file, 
							  const char *destination_path, 
							  qbool case_sensitive, 
							  qbool keep_path, 
							  qbool overwrite, 
							  const char *password);

int COM_ZipGetFirst (unzFile zip_file, sys_dirent *ent);

int COM_ZipGetNextFile (unzFile zip_file, sys_dirent *ent);

#endif // WITH_ZIP

#endif /* __COMMON_H__ */
