/*
    Python Samba Password Hash Generating module
    
    Copyright (C) 2002 Barry Pederson <bp@barryp.org>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

    -----------------

    2002-10-27  Initial version

*/

 
#include "Python.h" 
#include <memory.h>
#include <ctype.h>

#define LMPASSWDLEN 14

/* from md4.c and smbdes.c */
void mdfour(unsigned char *out, unsigned char *in, int n);
void E_P16(unsigned char *p14,unsigned char *p16);


static char module_doc [] =
"This module generates SMB lanman and nt password\n\
hashes suitable for use with Samba.\n\
\n\
Functions:\n\
\n\
  lmhash(passwd) -- return a string containing the lanman\n\
                    hash of the password\n\
  nthash(passwd) -- return a string containing the nt hash\n\
                    of the password\n\
  hash(passwd)   -- return a tuple containing the both the\n\
                    lanman hash and the nt hash strings\n\
";


/*
  convert 16-byte binary buffer to 32 hex-char Python string
*/
static char HEXCHARS[] = "0123456789ABCDEF";

static PyObject *
hash_to_string(char *tmp) 
    {
    int i;
    unsigned char c;
    char outbuffer[32];

    /* build string from binary hash */
    for(i = 0; i < 16; i++) 
        {
        c=tmp[i];
        outbuffer[ i*2   ] = HEXCHARS[(c>>4) & 0x0f];
        outbuffer[(i*2)+1] = HEXCHARS[   c   & 0x0f];
        }
        
    return PyString_FromStringAndSize(outbuffer, 32);
    }


static PyObject * 
lmhash(PyObject *self, PyObject *args)
    {
    char *pwd;
    int pwd_len;
    unsigned char lmpwd[LMPASSWDLEN+1];
    char hashout[17];
    int i;

    /* Unicode passwords are SOL I guess, python
       will convert to 8-bit chars here */
    if (!(PyArg_ParseTuple(args, "s#", &pwd, &pwd_len)))
        return NULL;

    /* make a copy that's truncated to 14 chars and uppercased */ 
    if (pwd_len > LMPASSWDLEN)       
        pwd_len = LMPASSWDLEN;
    memset(lmpwd, '\0', sizeof(lmpwd));
    for (i = 0; i < pwd_len; i++)
        lmpwd[i]=toupper(pwd[i]);        

    /* Generate the hash */
    memset(hashout,'\0',sizeof(hashout));
    E_P16(lmpwd, hashout);                
    
    /* clean things up  - don't know how much good it does since 
       Python presumably has other copies of the password floating 
       around, but what the hell - I'll do my part since I know it's
       safe.
    */
    memset(lmpwd, '\0', sizeof(lmpwd));
        
    return hash_to_string(hashout);
    }


static PyObject * 
nthash(PyObject *self, PyObject *args)
    {
    char *pwd;
    int pwd_len;
    char hashout[17];
         
    pwd = NULL;         
    if (!(PyArg_ParseTuple(args, "es#", "utf-16le", &pwd, &pwd_len)))
        return NULL;

    memset(hashout,'\0',sizeof(hashout));
    mdfour(hashout, pwd, pwd_len);        
    
    /* clean things up  - don't know how much good it does since 
       Python presumably has other copies of the password floating 
       around, but what the hell - I'll do my part since I'm pretty
       sure it's safe, from my understanding of PyArg_ParseTuple and "es#"
    */
    memset(pwd, '\0', pwd_len);
    PyMem_Free(pwd);
    
    return hash_to_string(hashout);
    }


static PyObject * 
hash(PyObject *self, PyObject *args)
    {
    PyObject *result;
    
    result = PyTuple_New(2);
    PyTuple_SetItem(result, 0, lmhash(self, args));
    PyTuple_SetItem(result, 1, nthash(self, args));
    
    return result;        
    }


/* List of functions exported by this module */
static PyMethodDef smbpasswd_functions[] = 
    {
    {"lmhash",  lmhash, METH_VARARGS},
    {"nthash",  nthash, METH_VARARGS},
    {"hash",    hash,   METH_VARARGS},
    {NULL,      NULL}   /* Sentinel */
    };


/* Initialize this module. */
void 
initsmbpasswd(void)
    {
    Py_InitModule3("smbpasswd", smbpasswd_functions, module_doc);
    }

/****** EOF *********/
