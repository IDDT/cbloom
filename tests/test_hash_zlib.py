import unittest
import os
import zlib
import cbloom


class TestHashZlib(unittest.TestCase):

    def setUp(self):
        self.items = tuple(os.urandom(x) for x in (0, 12, 836, 6548))

    def test_crc32(self):
        for x in self.items:
            with self.subTest(x=x):
                self.assertEqual(cbloom.crc32(x), zlib.crc32(x))

    def test_adler32(self):
        for x in self.items:
            with self.subTest(x=x):
                self.assertEqual(cbloom.adler32(x), zlib.adler32(x))
