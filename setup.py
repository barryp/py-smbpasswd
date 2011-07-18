#!/usr/bin/env python
#
# Python Distutils Setup file for py-smbpasswd module.  Build and
# install with:
#
#    python setup.py install
#
# 2002-10-27 Barry Pederson <bp@barryp.org>

import sys
from distutils.core import setup, Extension

setup(name = "smbpasswd",
      description = "SMB Password Hash Generator - suitable for use with Samba",
      version = "1.0.2",
      classifiers=[
          'Programming Language :: Python',
	  'License :: OSI Approved :: GNU General Public License (GPL)',
	  'Topic :: Software Development :: Libraries :: Python Modules',
          ],
      license = "GPL",
      author = "Barry Pederson",
      author_email = "bp@barryp.org",
      url = "http://code.google.com/p/py-smbpasswd/",
      ext_modules =
        [
        Extension("smbpasswd", ['md4.c', 'smbdes.c', 'smbpasswd.c'])
        ]
     )

##### That's all folks ###########
