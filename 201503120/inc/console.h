
//#define _MAX_USR_FT	0xff
#define PROMPT	     "PXA255-PRO>"	
#define MAXBUF		256
#define MAXARG		64

#define EOL		1
#define ARG		2
#define REP		3

#define _BS		0x08
#define _Esc		0x1b
#define _CR		0x0a
#define _LF		0x0d
#define _TAB		0x09
#define _SPAC		0x20
#define _AMPSND 	0x26
#define _SEMICLN	0x3b
#define _AST		0x2a
#define _STX		0x7e

//extern struct usr_ft_x;
extern struct USRFT_x ;

typedef void (*FUNCPTR) ();
typedef struct {
	char	*cmd;
	FUNCPTR ft;
	char	*msg;
	int	para_num;
	char	**help;
		}USRFT_x;

#define _UPPER         0x1		/* Upper case */
#define _LOWER         0x2		/* Lower case */
#define _NUMBER        0x4		/* Number */
#define _WHITE_SPACE   0x8		/* Whitespace */
#define _PUNCT         0x10		/* Punctuation */
#define _CONTROL       0x20		/* Control char */
#define _HEX_NUMBER    0x40		/* Hex digit */
#define _B             0x80		/* Blank */

#define	_U	0x1		/* Upper case */
#define	_L	0x2		/* Lower case */
#define	_N	0x4		/* Numeral (digit) */
#define	_S	0x8		/* Whitespace */
#define	_P	0x10	/* Punctuation */
#define	_C	0x20	/* Control character */
#define	_X	0x40	/* Hex */
#define	_B	0x80	/* blank */
#define NULL	'\0'

extern  unsigned char ctypetbl[];
#define isalpha(c)    (ctypetbl[(int)c] & (_U | _L))
#define isupper(c)    (ctypetbl[(int)c] & (_U))
#define islower(c)    (ctypetbl[(int)c] & (_L))
#define isdigit(c)    (ctypetbl[(int)c] & (_N))
#define isxdigit(c)   (ctypetbl[(int)c] & (_X))
#define isspace(c)    (ctypetbl[(int)c] & (_S | _C))
#define ispunct(c)    (ctypetbl[(int)c] & (_P))
#define isalnum(c)    (ctypetbl[(int)c] & (_U | _L | _N))
#define isprint(c)    (ctypetbl[(int)c] & (_P | _U | _L | _S | _N))
#define isgraph(c)    (ctypetbl[(int)c] & (_P | _U | _L | _N))
#define iscntrl(c)    (ctypetbl[(int)c] & (_C | _C_B))
#define toupper(c)    ((('a' <= (c))&&((c) <= 'z')) ? ((c) - 'a' + 'A') : (c))
#define tolower(c)    ((('A' <= (c))&&((c) <= 'Z')) ? ((c) - 'A' + 'a') : (c))

#define  CNUL   "" 
#define  CNRM   "\x1B[0;0m" /* &n */ 
#define  CRED   "\x1B[0;0m\x1B[31m" /* &r */ 
#define  CGRN   "\x1B[0;0m\x1B[32m" /* &g */ 
#define  CYEL   "\x1B[0;0m\x1B[33m" /* &y */ 
#define  CBLU   "\x1B[0;0m\x1B[34m" /* &b */ 
#define  CMAG   "\x1B[0;0m\x1B[35m" /* &m */ 
#define  CCYN   "\x1B[0;0m\x1B[36m" /* &c */ 
#define  CWHT   "\x1B[0;0m\x1B[37m" /* &w */ 
#define  CBLK   "\x1B[0;0m\x1B[30m" /* &l */ 
#define  BRED   "\x1B[1;31m" /* &R */ 
#define  BGRN   "\x1B[1;32m" /* &G */ 
#define  BYEL   "\x1B[1;33m" /* &Y */ 
#define  BBLU   "\x1B[1;34m" /* &B */ 
#define  BMAG   "\x1B[1;35m" /* &M */ 
#define  BCYN   "\x1B[1;36m" /* &C */ 
#define  BWHT   "\x1B[1;37m" /* &W */ 
#define  BBLK   "\x1B[1;30m" /* &L */ 
#define  BKRED   "\x1B[41m" /* &e */ 
#define  BKGRN   "\x1B[42m" /* &k */ 
#define  BKYEL   "\x1B[43m" /* &p */ 
#define  BKBLU   "\x1B[44m" /* &u */ 
#define  BKMAG   "\x1B[45m" /* &a */ 
#define  BKCYN   "\x1B[46m" /* &f */ 
#define  BKWHT   "\x1B[47m" /* &h */ 
#define  BKBLK   "\x1B[40m" /* &i */ 
#define  UNDER   "\x1B[4m" /* &U */ 
#define  FLASH   "\x1B[5m" /* &F */ 
#define  MAX_COLORS   26 

#define	 RED	"\x1b[0m\x1b[01;31m"
#define  GREEN  "\x1b[0m\x1b[01;32m"
#define  BLACK  "\x1b[0m"

