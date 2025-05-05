using LinearAlgebra;
using System;
using System.Numerics;
class Program
{
    static void Main(string[] args)
    {
        IMathVector vector = new MathVector(new double[] { 1, 2, 3 });
        Console.WriteLine(vector.GetEnumerator());

    }

    internal void TestInConsole()
    {
        IMathVector vector;
        IMathVector vector2;
        IMathVector vector3;
        try
        {
            vector = new MathVector(new double[] { 3, 4, 5 });
            vector2 = new MathVector(new double[] { 1, 2, 3 });
            vector3 = new MathVector(new double[] { 2, 4 });

            Console.WriteLine(vector);
        }
        catch (Exception e)
        {
            Console.WriteLine($"Ошибка при вызове инициализации: {e.Message}\n");
            return;
        }

        try
        {
            IMathVector vectorSet = vector.Set(1, 5);
            Console.Write("Координаты вектора после Set: ");
            PrintVector(vectorSet);
        }
        catch (Exception e)
        {
            Console.WriteLine($"Ошибка при вызове Set: {e.Message}\n");
        }

        try
        {
            Console.Write("Координаты вектора: ");
            PrintVector(vector);
        }
        catch (Exception e)
        {
            Console.WriteLine($"Ошибка при выводе вектора: {e.Message}\n");
        }

        try
        {
            Console.Write("Координаты вектора 2: ");
            PrintVector(vector2);
        }
        catch (Exception e)
        {
            Console.WriteLine($"Ошибка при выводе вектора 2: {e.Message}\n");
        }

        try
        {
            Console.WriteLine("Размерность вектора: " + vector.Dimensions);
            Console.WriteLine("Длина вектора: " + vector.Length);
        }
        catch (Exception e)
        {
            Console.WriteLine($"Ошибка при получении свойств вектора: {e.Message}\n");
        }

        try
        {
            IMathVector newVectorSum = vector.SumNumber(5);
            Console.Write("Координаты нового вектора, сложенного с числом: ");
            PrintVector(newVectorSum);
        }
        catch (Exception e)
        {
            Console.WriteLine($"Ошибка при сложении с числом: {e.Message}\n");
        }

        try
        {
            IMathVector newVectorMult = vector.MultiplyNumber(5);
            Console.Write("Координаты нового вектора, умноженного на число: ");
            PrintVector(newVectorMult);
        }
        catch (Exception e)
        {
            Console.WriteLine($"Ошибка при умножении на число: {e.Message}\n");
        }

        try
        {
            Console.WriteLine("Скалярное произведение векторов: " + vector.ScalarMultiply(vector2));
        }
        catch (Exception e)
        {
            Console.WriteLine($"Ошибка при вычислении скалярного произведения: {e.Message}\n");
        }

        try
        {
            IMathVector newVectorMultVec = vector.Multiply(vector2);
            Console.Write("Координаты нового вектора, умноженного на исходный вектор: ");
            PrintVector(newVectorMultVec);
        }
        catch (Exception e)
        {
            Console.WriteLine($"Ошибка при умножении векторов: {e.Message}\n");
        }

        try
        {
            IMathVector newVectorSumVec = vector.Sum(vector2);
            Console.Write("Координаты нового вектора, сложенного с исходным вектором: ");
            PrintVector(newVectorSumVec);
        }
        catch (Exception e)
        {
            Console.WriteLine($"Ошибка при сложении векторов: {e.Message}\n");
        }

        try
        {
            Console.WriteLine("Расстояние от вектора1 до вектора2: " + vector.CalcDistance(vector2));
        }
        catch (Exception e)
        {
            Console.WriteLine($"Ошибка при вычислении расстояния: {e.Message}\n");
        }

        try
        {
            IMathVector newVectorPlus = (MathVector)vector + (MathVector)vector2;
            Console.Write("vector1 + vector2: ");
            PrintVector(newVectorPlus);
        }
        catch (Exception e)
        {
            Console.WriteLine($"Ошибка при сложении векторов через оператор +: {e.Message}\n");
        }

        try
        {
            IMathVector newVectorMinus = (MathVector)vector - 5;
            Console.Write("vector1 - 5: ");
            PrintVector(newVectorMinus);
        }
        catch (Exception e)
        {
            Console.WriteLine($"Ошибка при вычитании числа из вектора: {e.Message}\n");
        }

        try
        {
            IMathVector newVectorMinusVec = (MathVector)vector - (MathVector)vector2;
            Console.Write("vector1 - vector2: ");
            PrintVector(newVectorMinusVec);
        }
        catch (Exception e)
        {
            Console.WriteLine($"Ошибка при вычитании векторов: {e.Message}\n");
        }

        try
        {
            IMathVector newVectorDivVec2 = (MathVector)vector / (MathVector)vector2;
            Console.Write("vector1 / vector2: ");
            PrintVector(newVectorDivVec2);
        }
        catch (Exception e)
        {
            Console.WriteLine($"Ошибка при делении векторов: {e.Message}\n");
        }

        try
        {
            double newScalar = (MathVector)vector % (MathVector)vector2;
            Console.Write("vector1 % vector2: " + newScalar);
        }
        catch (Exception e)
        {
            Console.WriteLine($"Ошибка при вычислении остатка от деления векторов: {e.Message}\n");
        }
    }

    internal static void PrintVector(IMathVector vector)
    {
        for (int i = 0; i < vector.Dimensions; i++)
        {
            Console.Write(vector[i] + " ");
        }
        Console.WriteLine();
    }
}