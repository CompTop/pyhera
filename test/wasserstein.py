import unittest
from hera_tda import WassersteinDistance
from hera_tda.wasserstein import AuctionParams

class TestWassersteinDistance(unittest.TestCase):

	def setUp(self):
		pass

	def test_distance1(self):
		pX = [[1.0, 2.0], [2.0,3.0]]
		pY = [[1.1, 2.1], [2.1, 3.1]]
		d = WassersteinDistance(pX, pY, 1.0)
		self.assertAlmostEqual(d, 0.2)

		param = AuctionParams()
		param.wasserstein_power = 1.0
		d = WassersteinDistance(pX, pY, param)
		self.assertAlmostEqual(d, 0.2)

	def test_distance2(self):
		pX = [[1.0, 2.0], [2.0,3.0]]
		pY = [[1.1, 2.1], [2.1, 3.1]]
		d = WassersteinDistance(pX, pY, 2.0)
		self.assertAlmostEqual(d, 0.14142135623730964)

		param = AuctionParams()
		param.wasserstein_power = 2.0
		d = WassersteinDistance(pX, pY, param)
		self.assertAlmostEqual(d, 0.14142135623730964)




if __name__ == '__main__':
    unittest.main()
