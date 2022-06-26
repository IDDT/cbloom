import unittest
from cbloom import Bloom


class TestBloom(unittest.TestCase):

    def setUp(self):
        self.items = [
            4, -4, 'abc', 'อักษรไทย', 3.1415, tuple('abc'), -193914191749714
        ]

    def test_init(self):
        self.assertIsInstance(Bloom(100), Bloom)

    def test_len(self):
        self.assertEqual(Bloom(101).len(), 101)
        self.assertEqual(Bloom(9).len(), 9)

    def test_missing(self):
        b = Bloom(101)
        [self.assertFalse(b.has(x)) for x in self.items]

    def test_put(self):
        b = Bloom(101)
        [self.assertIsNone(b.put(x)) for x in self.items]
        [self.assertTrue(b.has(x)) for x in self.items]

    def test_clear(self):
        b = Bloom(101)
        [self.assertIsNone(b.put(x)) for x in self.items]
        [self.assertTrue(b.has(x)) for x in self.items]
        self.assertIsNone(b.clear())
        [self.assertFalse(b.has(x)) for x in self.items]
