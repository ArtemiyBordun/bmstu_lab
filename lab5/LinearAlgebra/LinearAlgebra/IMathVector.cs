using System;
using System.Collections;
using System.Collections.Generic;

public interface IMathVector : IEnumerable
{                       
    int Dimensions { get; }                                     // Получить размерность вектора (количество координат)
    double this[int i] { get; set; }                             // Индексатор для доступа к элементам вектора. Нумерация с нуля.
    IMathVector Set(int index, double value);
    double Length { get; }                                      // Рассчитать длину(модуль) вектора
    IMathVector SumNumber(double number);                       // Покомпонентное сложение с числом
    IMathVector MultiplyNumber(double number, bool multiply = true);                  // Покомпонентное умножение на число
    IMathVector Sum(IMathVector vector);                        // Сложение с другим вектором
    IMathVector Multiply(IMathVector vector);                   // Покомпонентное умножение с другим вектором
    double ScalarMultiply(IMathVector vector);                  // Скалярное умножение на другой вектор
    double CalcDistance(IMathVector vector);                    // Вычислить Евклидово расстояние до другого вектора


} 