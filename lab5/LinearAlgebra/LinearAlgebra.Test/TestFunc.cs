using System.Numerics;

namespace LinearAlgebra.Test
{
    [TestClass]
    public class TestFunc
    {
        [TestMethod]
        public void TestGet()
        {
            IMathVector vector = new MathVector(new double[] { 3, 4, 5 });
            Assert.AreEqual(4, vector[1]);
        }
        [TestMethod]
        public void TestSet()
        {
            IMathVector vector = new MathVector(new double[] { 2, 4, 4 });
            IMathVector newVector = vector.Set(1, 11);
            Assert.AreEqual(11, newVector[1]);
        }
        [TestMethod]
        public void TestSumNum()
        {
            IMathVector vector = new MathVector(new double[] { 2, 4, 4 });
            IMathVector sumVector = vector.SumNumber(6);
            Assert.AreEqual(8, sumVector[0]);
        }
        [TestMethod]
        public void TestSum()
        {
            IMathVector vector = new MathVector(new double[] { 2, 4, 4 });
            IMathVector vector1 = new MathVector(new double[] { 1, 2, 3 });
            IMathVector sumVector = vector.Sum(vector1);
            Assert.AreEqual(6, sumVector[1]);
        }
        [TestMethod]
        public void TestMultiplyNum()
        {
            IMathVector vector = new MathVector(new double[] { 2, 4, 4 });
            IMathVector multVector = vector.MultiplyNumber(2);
            Assert.AreEqual(8, multVector[1]);
        }
        [TestMethod]
        public void TestMultiply()
        {
            IMathVector vector = new MathVector(new double[] { 2, 4, 4 });
            IMathVector vector1 = new MathVector(new double[] { 1, 2, 3 });
            IMathVector multVector = vector.Multiply(vector1);
            Assert.AreEqual(8, multVector[1]);
        }
        [TestMethod]
        public void TestDivNum()
        {
            IMathVector vector = new MathVector(new double[] { 2, 4, 4 });
            IMathVector multVector = vector.MultiplyNumber(0.5);
            Assert.AreEqual(2, multVector[1]);
        }
        public void TestSubtractionNum()
        {
            IMathVector vector = new MathVector(new double[] { 2, 4, 4 });
            IMathVector sumVector = vector.SumNumber(-6);
            Assert.AreEqual(-4, sumVector[0]);
        }
        [TestMethod]
        public void TestScalarMultiply()
        {
            IMathVector vector = new MathVector(new double[] { 3, 4, 5 });
            IMathVector vector1 = new MathVector(new double[] { 1, 2, 3 });
            double scalar = vector.ScalarMultiply(vector1);
            Assert.AreEqual(26, scalar);
        }
        [TestMethod]
        public void TestCalcDistance()
        {
            IMathVector vector = new MathVector(new double[] { 1, 2, 3 });
            IMathVector vector1 = new MathVector(new double[] { 0, 10, 7 });
            double distance = vector.CalcDistance(vector1);
            Assert.AreEqual(9, distance);
        }
        [TestMethod]
        public void TestGetMoreLenght()
        {
            IMathVector vector = new MathVector(new double[] { 1, 2, 3 });
            Assert.ThrowsException<IndexOutOfRangeException>(() => vector[4]);
        }
        [TestMethod]
        public void TestSetMoreLenght()
        {
            IMathVector vector = new MathVector(new double[] { 1, 2, 3 });
            Assert.ThrowsException<IndexOutOfRangeException>(() => vector.Set(4, 21));
        }
        [TestMethod]
        public void TestGetLessLenght()
        {
            IMathVector vector = new MathVector(new double[] { 1, 2, 3 });
            Assert.ThrowsException<IndexOutOfRangeException>(() => vector[-1]);
        }
        [TestMethod]
        public void TestSetLessLenght()
        {
            IMathVector vector = new MathVector(new double[] { 1, 2, 3 });
            Assert.ThrowsException<IndexOutOfRangeException>(() => vector.Set(-1, 21));
        }
        [TestMethod]
        public void TestNotSet()
        {
            IMathVector vector = new MathVector(new double[] { 1, 2, 3 });
            Assert.ThrowsException<NotSupportedException>(() => vector[0] = 1);
        }
        //[TestMethod]
        public void TestEnumerator()
        {
            IMathVector vector = new MathVector(new double[] { 1, 2, 3 });

            Assert.ThrowsException<NotSupportedException>(() => vector[0] = 1);
        }
        [TestMethod]
        public void TestMultiplyDiff()
        {
            IMathVector vector = new MathVector(new double[] { 1, 2, 3 });
            IMathVector vector1 = new MathVector(new double[] { 1, 2 });
            Assert.ThrowsException<ArgumentException>(() => vector.Multiply(vector1));
        }
        [TestMethod]
        public void TestSumDiff()
        {
            IMathVector vector = new MathVector(new double[] { 1, 2, 3 });
            IMathVector vector1 = new MathVector(new double[] { 1, 2 });
            Assert.ThrowsException<ArgumentException>(() => vector.Sum(vector1));
        }
        [TestMethod]
        public void TestScalarDiff()
        {
            IMathVector vector = new MathVector(new double[] { 1, 2, 3 });
            IMathVector vector1 = new MathVector(new double[] { 1, 2 });
            Assert.ThrowsException<ArgumentException>(() => vector.ScalarMultiply(vector1));
        }
        [TestMethod]
        public void TestMultiplyDiff1()
        {
            IMathVector vector = new MathVector(new double[] { 1, 2});
            IMathVector vector1 = new MathVector(new double[] { 1, 2, 5 });
            Assert.ThrowsException<ArgumentException>(() => vector.Multiply(vector1));
        }
        [TestMethod]
        public void TestSumDiff1()
        {
            IMathVector vector = new MathVector(new double[] { 1, 2 });
            IMathVector vector1 = new MathVector(new double[] { 1, 2, 5 });
            Assert.ThrowsException<ArgumentException>(() => vector.Sum(vector1));
        }
        [TestMethod]
        public void TestScalarDiff1()
        {
            IMathVector vector = new MathVector(new double[] { 1, 2});
            IMathVector vector1 = new MathVector(new double[] { 1, 2, 5 });
            Assert.ThrowsException<ArgumentException>(() => vector.ScalarMultiply(vector1));
        }
    }
}