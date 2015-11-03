[![Build Status](https://travis-ci.org/barryp/py-smbpasswd.svg?branch=trunk)](https://travis-ci.org/barryp/py-smbpasswd)

smbpasswd
=========

    Python SMB Password Hash Generator module

    2002-10-27 Barry Pederson <bp@barryp.org>

INSTALLATION
------------

1. Unpack the distribution.

        tar xzvf smbpasswd-1.0.2.tgz

2. Compile and install.

        cd smbpasswd-1.0.2
        python setup.py install


SAMPLE USAGE
------------

In Python:

    import smbpasswd

    passwd = 'mypassword'

    print 'LANMAN hash is', smbpasswd.lmhash(passwd)
    print 'NT hash is', smbpasswd.nthash(passwd)

    print 'both hashes at once = %s:%s' % smbpasswd.hash(passwd)

------------------------------------------------------------
                                            Enjoy

