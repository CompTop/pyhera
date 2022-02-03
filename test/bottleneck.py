import unittest
from hera_tda import BottleneckDistance

class TestBottleneckDistance(unittest.TestCase):

	def setUp(self):
		pass

	def test_distance(self):
		pX = [[1.0, 2.0], [2.0,3.0]]
		pY = [[1.1, 2.1], [2.1, 3.1]]
		d, inds = BottleneckDistance(pX, pY)
		self.assertAlmostEqual(d, 0.1)


if __name__ == '__main__':
    unittest.main()
