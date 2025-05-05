using System.Numerics;

namespace LinearAlgebra.Test
{
    [TestClass]
    public class TestConstructor
    {
        [TestMethod]
        public void TestDimensions()
        {
            IMathVector vector = new MathVector(new double[] { 3, 4, 5 });
            Assert.AreEqual(3, vector.Dimensions);
        }
        [TestMethod]
        public void TestNull()
        {
            Assert.ThrowsException<ArgumentNullException>(() => new MathVector(null));
        }
        [TestMethod]
        public void TestZeroLenght()
        {
            Assert.ThrowsException<ArgumentNullException>(() => new MathVector(new double[] { }));
        }
        [TestMethod]
        public void TestLength()
        {
            IMathVector vector = new MathVector(new double[] { 2, 4, 4 });
            Assert.AreEqual(6, vector.Length);
        }
    }
}