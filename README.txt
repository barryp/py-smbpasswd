smbpasswd

    Python SMB Password Hash Generator module

    2002-10-27 Barry Pederson <bp@barryp.org>

INSTALLATION
------------

1. Unpack the distribution.

        tar xzvf py-smbpasswd-1.0.1.tar.gz

2. Compile and install.

        cd py-smbpasswd-1.0.1
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

