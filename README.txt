smbpasswd

    Python SMB Password Hash Generator module

    2002-10-27 Barry Pederson <bp@barryp.org>

INSTALLATION
------------

1. Unpack the distribution.

        tar xzvf py-smbpasswd-1.0.tar.gz

2. Compile and install.

        cd py-smbpasswd-1.0
        python setup.py install


SAMPLE USAGE
------------

In Python:

    import smbpasswd

    pwd = 'mypassword'

    print 'LANMAN hash is', smbpasswd.lmhash(pwd)
    print 'NT hash is', smbpasswd.nthash(pwd)

    print 'both hashes at once = %s:%s' % smbpasswd.hash(pwd)

------------------------------------------------------------
                                            Enjoy

