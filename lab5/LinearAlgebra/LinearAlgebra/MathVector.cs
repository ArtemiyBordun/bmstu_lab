using System.Collections;
using System.Numerics;
using System.Reflection.Metadata.Ecma335;
using System.Runtime.CompilerServices;

namespace LinearAlgebra
{
    public class MathVector : IMathVector
    {
        private double[] _coordinates;
        private double _length;

        public MathVector(double[] coordinates)
        {
            if (coordinates == null || coordinates.Length == 0)
                throw new ArgumentNullException("Размерность вектора не может быть 0");
            _coordinates = coordinates;

            double len = 0;
            for (int i = 0; i < _coordinates.Length; i++)
            {
                len += Math.Pow(_coordinates[i], 2);
            }
            _length = Math.Abs(Math.Sqrt(len));
        }

        public int Dimensions => _coordinates.Length;

        public double this[int i]
        {
            get
            {
                return (i >= 0 & i < _coordinates.Length) ? _coordinates[i] : 
                    throw new IndexOutOfRangeException("Индекс выходит за пределы массива");
            }

            set => throw new NotSupportedException("Векторы нельзя изменить через индексаторы, используйте метод Set()"); //? 
        }

        public IMathVector Set(int index, double value)
        {
            if (index < 0 || index >= _coordinates.Length)
                throw new IndexOutOfRangeException("Индекс выходит за пределы массива");

            double[] newCoords = (double[])_coordinates.Clone();
            newCoords[index] = value;

            IMathVector productVector = new MathVector(newCoords);
            return productVector;
        }

        public double Length => _length;

        public IEnumerator GetEnumerator()
        {
            return _coordinates.GetEnumerator();
        }

        public IMathVector Multiply(IMathVector vector)
        {
            if (vector == null || Dimensions != vector.Dimensions)
                throw new ArgumentException("Размерность векторов должна совпадать!");

            double[] newCoords = new double[Dimensions];
            for (int i = 0; i < Dimensions; i++)
                 newCoords[i] += _coordinates[i] * vector[i];

            IMathVector productVector = new MathVector(newCoords);
            return productVector;
        }

        private IMathVector MultiplyDiv(IMathVector vector, bool multiply = true)
        {
            if (vector == null || Dimensions != vector.Dimensions)
                throw new ArgumentException("Размерность векторов должна совпадать!");

            double[] newCoords = new double[Dimensions];
            for (int i = 0; i < Dimensions; i++)
            {
                if (multiply)
                    newCoords[i] += _coordinates[i] * vector[i];
                else
                {
                    if (vector[i] == 0)
                        throw new DivideByZeroException("Не дели на 0 по братски");
                    newCoords[i] += _coordinates[i] / vector[i];
                }
            }
            IMathVector productVector = new MathVector(newCoords);
            return productVector;
        }

        public IMathVector MultiplyNumber(double number, bool multiply = true)
        {
            if (!multiply)
            {
                if (number == 0)
                    throw new DivideByZeroException("Не дели на 0 по братски");
                else
                    number = 1 / number;
            }
            double[] newCoords = new double[_coordinates.Length];
            for (int i = 0; i < newCoords.Length; i++)
            {
                newCoords[i] = _coordinates[i] * number;
            }
            IMathVector newVector = new MathVector(newCoords);
            return newVector;
        }

        public IMathVector Sum(IMathVector vector)
        {
            if (vector == null || Dimensions != vector.Dimensions)
                throw new ArgumentException("Размерность векторов должна совпадать!");
            double[] newCoords = new double[Dimensions];
            for (int i = 0; i < Dimensions; i++)
                 newCoords[i] += _coordinates[i] + vector[i];

            IMathVector sumVector = new MathVector(newCoords);
            return sumVector;
        }

        private IMathVector SumSubtraction(IMathVector vector, bool sum = true)
        {
            if (vector == null || Dimensions != vector.Dimensions)
                throw new ArgumentException("Размерность векторов должна совпадать!");
            double[] newCoords = new double[Dimensions];
            for (int i = 0; i < Dimensions; i++)
            {
                if (sum)
                    newCoords[i] += _coordinates[i] + vector[i];
                else
                    newCoords[i] += _coordinates[i] - vector[i];

            }
            IMathVector sumVector = new MathVector(newCoords);
            return sumVector;
        }

        public IMathVector SumNumber(double number)
        {
            double[] newCoords = new double[_coordinates.Length];
            for (int i = 0; i < newCoords.Length; i++)
            {
                newCoords[i] = _coordinates[i] + number;
            }
            IMathVector newVector = new MathVector(newCoords);
            return newVector;
        }

        public double ScalarMultiply(IMathVector vector)
        {
            double scalar = 0;
            if (vector == null || Dimensions != vector.Dimensions)
                throw new ArgumentException("Размерность векторов должна совпадать!");

            for (int i = 0; i < Dimensions; i++)
            {
                scalar += _coordinates[i] * vector[i];
            }
            return scalar;
        }

        public double CalcDistance(IMathVector vector)
        {
            if (vector == null || Dimensions != vector.Dimensions)
                throw new ArgumentException("Размерность векторов должна совпадать!");

            double distance = 0;
            for (int i = 0; i < Dimensions; i++)
            {
                distance += Math.Pow((_coordinates[i] - vector[i]), 2);
            }

            return Math.Sqrt(distance);
        }

        public static IMathVector operator +(MathVector vector, double number) => (MathVector)vector.SumNumber(number);
        public static IMathVector operator +(MathVector vector, MathVector vector2) => vector.Sum(vector2);
        public static IMathVector operator -(MathVector vector, double number) => (MathVector)vector.SumNumber(-number);
        public static IMathVector operator -(MathVector vector, IMathVector vector2) => (MathVector)vector.SumSubtraction(vector2, false);
        public static IMathVector operator *(MathVector vector, double number) => (MathVector)vector.MultiplyNumber(number);
        public static IMathVector operator *(MathVector vector, MathVector vector2) => (MathVector)vector.Multiply(vector2);
        public static IMathVector operator /(MathVector vector, double number) => (MathVector)vector.MultiplyNumber(number, false);
        public static IMathVector operator /(MathVector vector, IMathVector vector2) => (MathVector)vector.MultiplyDiv(vector2, false);
        public static double operator %(MathVector vector, MathVector vector2) => vector.ScalarMultiply(vector2);
    }
}
