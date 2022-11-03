#define CATCH_CONFIG_MAIN

#include "../catch2/catch.hpp"
#include <iostream>

struct ListNode
{
public:
    ListNode(int value, ListNode* prev = nullptr, ListNode* next = nullptr)
        : value(value), prev(prev), next(next)
    {
        if (prev != nullptr) prev->next = this;
        if (next != nullptr) next->prev = this;
    }

public:
    int value;
    ListNode* prev;
    ListNode* next;
};


class List
{
public:
    List()
        : m_head(new ListNode(static_cast<int>(0))), m_size(0),
        m_tail(new ListNode(0, m_head))
    {
    }

    virtual ~List()
    {
        Clear();
        delete m_head;
        delete m_tail;
    }

    bool Empty() { return m_size == 0; }

    unsigned long Size() { return m_size; }

    void PushFront(int value)
    {
        new ListNode(value, m_head, m_head->next);
        ++m_size;
    }

    void PushBack(int value)
    {
        new ListNode(value, m_tail->prev, m_tail);
        ++m_size;
    }

    int PopFront()
    {
        if (Empty()) throw std::runtime_error("list is empty");
        auto node = extractPrev(m_head->next->next);
        int ret = node->value;
        delete node;
        return ret;
    }

    int PopBack()
    {
        if (Empty()) throw std::runtime_error("list is empty");
        auto node = extractPrev(m_tail);
        int ret = node->value;
        delete node;
        return ret;
    }

    void Clear()
    {
        auto current = m_head->next;
        while (current != m_tail)
        {
            current = current->next;
            delete extractPrev(current);
        }
    }

private:
    ListNode* extractPrev(ListNode* node)
    {
        auto target = node->prev;
        target->prev->next = target->next;
        target->next->prev = target->prev;
        --m_size;
        return target;
    }

private:
    ListNode* m_head;
    ListNode* m_tail;
    unsigned long m_size;
};

TEST_CASE("test list_pushback_popback", "[pushback_popback]") {
    bool except_error = true;
    List list;
    CHECK(list.Empty() == true);
    CHECK(list.Size() == 0);
    //Проверяем реакцию PopBack на пустом списке
    try {
        list.PopBack();
    }
    catch (...) {
        //Исключение выброшено, поведение корректное. Как проверить выбрасывание исключения средствами catch не знаю
        list.PushBack(10);
        CHECK(list.Empty() == false);
        CHECK(list.Size() == 1);
        list.PushBack(11);
        CHECK(list.Empty() == false);
        CHECK(list.Size() == 2);
        CHECK(list.PopBack() == 11);
        CHECK(list.Empty() == false);
        CHECK(list.Size() == 1);
        CHECK(list.PopBack() == 10);
        CHECK(list.Empty() == true);
        CHECK(list.Size() == 0);
        except_error = false;
    }
    if (except_error) {
        std::cout << "\nPopBack in empty list error!!!\n";  //Как проверить выбрасывание исключения средствами catch не знаю
    }
}

TEST_CASE("test list_pushfront_popback", "[pushfront_popback]") {
    bool except_error = true;
    List list;
    CHECK(list.Empty() == true);
    CHECK(list.Size() == 0);
    //Проверяем реакцию PopFront на пустом списке
    try {
        list.PopFront();
    }
    catch (...) {
        //Исключение выброшено, поведение корректное. Как проверить выбрасывание исключения средствами catch не знаю
        list.PushFront(10);
        CHECK(list.Empty() == false);
        CHECK(list.Size() == 1);
        list.PushFront(11);
        CHECK(list.Empty() == false);
        CHECK(list.Size() == 2);
        CHECK(list.PopFront() == 11);
        CHECK(list.Empty() == false);
        CHECK(list.Size() == 1);
        CHECK(list.PopFront() == 10);
        CHECK(list.Empty() == true);
        CHECK(list.Size() == 0);
        except_error = false;
    }
    if (except_error) {
        std::cout << "\nPopFront in empty list error!!!\n";  //Как проверить выбрасывание исключения средствами catch не знаю
    }
}
