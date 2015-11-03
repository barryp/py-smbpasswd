import unittest
import smbpasswd

class SMBPasswdTests(unittest.TestCase):
    def test_lm(self):
        self.assertEqual(smbpasswd.lmhash('foo'), '5BFAFBEBFB6A0942AAD3B435B51404EE')
        self.assertEqual(smbpasswd.lmhash('passphrase'), '855C3697D9979E78AC404C4BA2C66533')


    def test_nt(self):
        self.assertEqual(smbpasswd.nthash('foo'), 'AC8E657F83DF82BEEA5D43BDAF7800CC')
        self.assertEqual(smbpasswd.nthash('passphrase'), '7F8FE03093CC84B267B109625F6BBF4B')

if __name__ == '__main__':
    unittest.main()