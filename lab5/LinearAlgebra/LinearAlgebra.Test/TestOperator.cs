using System.Numerics;

namespace LinearAlgebra.Test
{
    [TestClass]
    public class TestOperator
    {
        [TestMethod]
        public void TestPlusNum()
        {
            IMathVector vector = new MathVector(new double[] { 3, 4, 5 });
            IMathVector plusVector = (MathVector)vector + 6;
            Assert.AreEqual(9, plusVector[0]);
        }
        [TestMethod]
        public void TestPlus()
        {
            IMathVector vector = new MathVector(new double[] { 3, 4, 5 });
            IMathVector vector1 = new MathVector(new double[] { 1, 2, 5 });
            IMathVector plusVector = (MathVector)vector + (MathVector)vector1;
            Assert.AreEqual(4, plusVector[0]);
        }
        [TestMethod]
        public void TestMinusNum()
        {
            IMathVector vector = new MathVector(new double[] { 3, 4, 5 });
            IMathVector minusVector = (MathVector)vector - 3;
            Assert.AreEqual(0, minusVector[0]);
        }
        [TestMethod]
        public void TestMinus()
        {
            IMathVector vector = new MathVector(new double[] { 3, 4, 5 });
            IMathVector vector1 = new MathVector(new double[] { 1, 2, 5 });
            IMathVector minusVector = (MathVector)vector - (MathVector)vector1;
            Assert.AreEqual(2, minusVector[0]);
        }
        [TestMethod]
        public void TestMultNum()
        {
            IMathVector vector = new MathVector(new double[] { 3, 4, 5 });
            IMathVector multVector = (MathVector)vector * 6;
            Assert.AreEqual(18, multVector[0]);
        }
        [TestMethod]
        public void TestMult()
        {
            IMathVector vector = new MathVector(new double[] { 3, 4, 5 });
            IMathVector vector1 = new MathVector(new double[] { 1, 2, 5 });
            IMathVector multVector = (MathVector)vector * (MathVector)vector1;
            Assert.AreEqual(3, multVector[0]);
        }
        [TestMethod]
        public void TestDivNum()
        {
            IMathVector vector = new MathVector(new double[] { 3, 4, 5 });
            IMathVector divVector = (MathVector)vector / 2;
            Assert.AreEqual(2, divVector[1]);
        }
        [TestMethod]
        public void TestDiv()
        {
            IMathVector vector = new MathVector(new double[] { 3, 4, 5 });
            IMathVector vector1 = new MathVector(new double[] { 1, 2, 5 });
            IMathVector divVector = (MathVector)vector / (MathVector)vector1;
            Assert.AreEqual(3, divVector[0]);
        }
        [TestMethod]
        public void TestDivNumZero()
        {
            IMathVector vector = new MathVector(new double[] { 3, 4, 5 });
            Assert.ThrowsException<DivideByZeroException>(() => (MathVector)vector / 0);
        }
        [TestMethod]
        public void TestDivZero()
        {
            IMathVector vector = new MathVector(new double[] { 3, 4, 5 });
            IMathVector vector1 = new MathVector(new double[] { 1, 0, 5 });
            Assert.ThrowsException<DivideByZeroException>(() => (MathVector)vector / (MathVector)vector1);
        }
        [TestMethod]
        public void TestScalar()
        {
            IMathVector vector = new MathVector(new double[] { 3, 4, 5 });
            IMathVector vector1 = new MathVector(new double[] { 1, 2, 3 });
            double scalar = (MathVector)vector % (MathVector)vector1;
            Assert.AreEqual(26, scalar);
        }
        [TestMethod]
        public void TestScalarDiff()
        {
            IMathVector vector = new MathVector(new double[] { 3, 4, 5 });
            IMathVector vector1 = new MathVector(new double[] { 1, 2 });
            Assert.ThrowsException<ArgumentException>(() => (MathVector)vector % (MathVector)vector1);
        }
        [TestMethod]
        public void TestSumDiff()
        {
            IMathVector vector = new MathVector(new double[] { 3, 4, 5 });
            IMathVector vector1 = new MathVector(new double[] { 1, 2 });
            Assert.ThrowsException<ArgumentException>(() => (MathVector)vector + (MathVector)vector1);
        }
        [TestMethod]
        public void TestMultyDiff()
        {
            IMathVector vector = new MathVector(new double[] { 3, 4, 5 });
            IMathVector vector1 = new MathVector(new double[] { 1, 2 });
            Assert.ThrowsException<ArgumentException>(() => (MathVector)vector * (MathVector)vector1);
        }
        public void TestDivDiff()
        {
            IMathVector vector = new MathVector(new double[] { 3, 4, 5 });
            IMathVector vector1 = new MathVector(new double[] { 1, 2 });
            Assert.ThrowsException<ArgumentException>(() => (MathVector)vector / (MathVector)vector1);
        }
        [TestMethod]
        public void TestMinusDiff()
        {
            IMathVector vector = new MathVector(new double[] { 3, 4, 5 });
            IMathVector vector1 = new MathVector(new double[] { 1, 2 });
            Assert.ThrowsException<ArgumentException>(() => (MathVector)vector - (MathVector)vector1);
        }
        [TestMethod]
        public void TestScalarDiff1()
        {
            IMathVector vector = new MathVector(new double[] { 3, 4 });
            IMathVector vector1 = new MathVector(new double[] { 1, 2, 5 });
            Assert.ThrowsException<ArgumentException>(() => (MathVector)vector % (MathVector)vector1);
        }
        [TestMethod]
        public void TestSumDiff1()
        {
            IMathVector vector = new MathVector(new double[] { 3, 4 });
            IMathVector vector1 = new MathVector(new double[] { 1, 2, 5 });
            Assert.ThrowsException<ArgumentException>(() => (MathVector)vector + (MathVector)vector1);
        }
        [TestMethod]
        public void TestMultyDiff1()
        {
            IMathVector vector = new MathVector(new double[] { 3, 4 });
            IMathVector vector1 = new MathVector(new double[] { 1, 2, 5 });
            Assert.ThrowsException<ArgumentException>(() => (MathVector)vector * (MathVector)vector1);
        }
        public void TestDivDiff1()
        {
            IMathVector vector = new MathVector(new double[] { 3, 4 });
            IMathVector vector1 = new MathVector(new double[] { 1, 2, 5 });
            Assert.ThrowsException<ArgumentException>(() => (MathVector)vector / (MathVector)vector1);
        }
        [TestMethod]
        public void TestMinusDiff1()
        {
            IMathVector vector = new MathVector(new double[] { 3, 4 });
            IMathVector vector1 = new MathVector(new double[] { 1, 2, 5 });
            Assert.ThrowsException<ArgumentException>(() => (MathVector)vector - (MathVector)vector1);
        }
    }
}