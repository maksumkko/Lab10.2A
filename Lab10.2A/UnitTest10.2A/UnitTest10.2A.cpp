#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab10.2A/Lab10.2A.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest102A
{
	TEST_CLASS(UnitTest102A)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Students students[] = {
				{ "Іванов", 1, ITIS, 4, 5, 3 },
				{ "Петров", 2, RE, 4, 4, 4 },
				{ "Сидоров", 3, KN, 5, 3, 4 },
				{ "Денисов", 4, KI, 4, 4, 5 },
				{ "Миколаєв", 5, PZ, 3, 5, 4 },
			};
			int N = sizeof(students) / sizeof(students[0]);

			// Arrange: змінні для підрахунку
			int count_math = 0, count_physics = 0, count_info = 0, count_physics_5 = 0;

			// Act: викликаємо функцію для підрахунку
			count_good_grades(students, N, count_math, count_physics, count_info, count_physics_5);

			// Assert: перевіряємо, чи правильно пораховані кількості
			Assert::AreEqual(count_math, 2);
		}
	};
}