#include "pch.h"
#include "CppUnitTest.h"
#include "Header.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(OrderTests)
    {
    public:
        // Перевіряє що товар успішно додається і total рахується правильно
        // apple x3 = 3 * 10.5 = 31.5
        TEST_METHOD(AddProduct_CorrectTotal)
        {
            Order order;
            order.addProduct("apple", 3);
            Assert::AreEqual(31.5, order.getTotal(), 0.001);
        }

        // Перевіряє що після видалення товару total змінюється
        // залишається тільки banana x1 = 8.2
        TEST_METHOD(RemoveProduct_UpdatesTotal)
        {
            Order order;
            order.addProduct("apple", 2);
            order.addProduct("banana", 1);
            order.removeProduct("apple");
            Assert::AreEqual(8.2, order.getTotal(), 0.001);
        }

        // Перевіряє що промокод SALE20 застосовує знижку 20%
        // apple x10 = 105.0 → після знижки = 84.0
        TEST_METHOD(PromoCode_Sale20)
        {
            Order order;
            order.addProduct("apple", 10);
            order.applyPromoCode("SALE20");
            Assert::AreEqual(84.0, order.getTotal(), 0.001);
        }

        // Перевіряє акцію yogurt -15% при купівлі milk >= 2
        // milk x2 = 50.0, yogurt = 20.0 * 0.85 = 17.0 → разом 67.0
        TEST_METHOD(LoyaltyDeal_YogurtWithMilk)
        {
            Order order;
            order.setLoyaltyCard(true);
            order.addProduct("milk", 2);
            order.addProduct("yogurt", 1);
            order.checkout("Test St", 1);
            Assert::AreEqual(67.0, order.getTotal(), 0.001);
        }

        // Перевіряє що без картки лояльності акції не застосовуються
        // banana x2 = 16.4, yogurt = 20.0 → разом 36.4
        TEST_METHOD(NoDealsWithoutLoyaltyCard)
        {
            Order order;
            order.setLoyaltyCard(false);
            order.addProduct("banana", 2);
            order.addProduct("yogurt", 1);
            order.checkout("Test St", 1);
            Assert::AreEqual(36.4, order.getTotal(), 0.001);
        }

        // НЕПРАВИЛЬНИЙ ТЕСТ: очікує 99.0, але правильна відповідь 84.0
        // apple x10 = 105.0, знижка SALE20 = -20% → має бути 84.0
        TEST_METHOD(PromoCode_WrongExpected)
        {
            Order order;
            order.addProduct("apple", 10);
            order.applyPromoCode("SALE20");
            Assert::AreEqual(99.0, order.getTotal(), 0.001); // навмисно неправильне значення
        }
    };
}