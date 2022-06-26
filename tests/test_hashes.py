import unittest
import random
import string
import zlib
import cbloom


def rand_str(size:int, chars:str=string.ascii_letters + string.digits) -> str:
    return ''.join(random.choice(chars) for _ in range(size))


class TestHashes(unittest.TestCase):

    def setUp(self):
        self.items = [
            *[rand_str(x).encode('utf-8') for x in (0, 12, 836, 6548)],
            'อักษรไทย'.encode('utf-8'),
            (1024).to_bytes(2, byteorder='big')
        ]

    def test_crc32(self):
        for x in self.items:
            self.assertEqual(cbloom.crc32(x), zlib.crc32(x))
