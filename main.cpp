#include <iostream>
#include <string.h>
using namespace std;

class admin;
class student;

class course_info
{
public:
    string name;
    int id, capacity;
    course_info(string name_in, int id_in, int capacity_in)
    {
        name = name_in;
        id = id_in;
        capacity = capacity_in;
    }
};

class student_info
{
public:
    string name;
    int id;
    student_info(string name_in, int id_in)
    {
        name = name_in;
        id = id_in;
    }
};

class undo_reg
{
public:
    int course_id, student_id;
    undo_reg(int course_id_in, int student_id_in)
    {
        course_id = course_id_in;
        student_id = student_id_in;
    }
};

template <typename T>
class stack
{
private:
    T *data;
    stack *prev;

public:
    stack(T *&data_in)
    {
        data = data_in;
        prev = NULL;
    }
    void add_node(stack *&start, T *&data_in)
    {
        if (start == NULL)
        {
            start = new stack(data_in);
            return;
        }
        else
        {
            stack *tmp_s = new stack(data_in);
            tmp_s->prev = start;
            start = tmp_s;
            return;
        }
    }
    int is_empty(stack *&start)
    {
        if (start == NULL)
            return 1;
        else
            return 0;
    }
    T *pop(stack *&start)
    {
        stack *tmp_s = start;
        if (start == NULL)
            cout << "what are you doing?\n";
        start = start->prev;
        return tmp_s->data;
    }
};

template <typename T>
class queue
{
private:
    T **data;
    int capacity, used;
    int first, end;

public:
    queue(int capacity_in)
    {
        data = new T *[capacity_in];
        capacity = capacity_in;
        used = 0;
        first = 0;
        end = 0;
    }
    int is_empty(queue *start)
    {
        if (start == NULL)
            return 1;
        if (start->used == 0)
            return 1;
        else
            return 0;
    }
    void add_node(queue *&start, T *&data_in)
    {
        if (start == NULL)
        {
            start = new queue(30);
        }
        if (start->used >= start->capacity)
        {
            cout << "error! full queue.\n";
        }
        else
        {
            start->data[start->end] = data_in;
            start->end = ((start->end) + 1) % (start->capacity);
            (start->used) += 1;
        }
    }
    T *&get_node(queue *&start)
    {
        // T* tmp_value=start->data[start->first];
        int tmp_value = start->first;
        start->first = ((start->first) + 1) % (start->capacity);
        start->used -= 1;
        return start->data[tmp_value];
    }
    void show(queue *&start)
    {
        cout << "first: " << start->first << endl;
        cout << "end: " << start->end << endl;
        cout << "used: " << start->used << endl;
        for (int i = start->first, j = 0; j < start->used; i = (i + 1) % start->capacity, j++)
        {
            start->data[i]->show(start->data[i]);
        }
    }
};

template <typename T>
class linked_list
{
public:
    T *data;
    linked_list *next, *prev;

    linked_list(T *&data_in)
    {
        data = data_in;
        next = NULL;
        prev = NULL;
    }
    void add_node(linked_list *&start, T *&data_in)
    {
        if (start == NULL)
        {
            start = new linked_list(data_in);
            return;
        }
        else
        {
            linked_list *tmp_l = start;
            while (tmp_l->next != NULL)
                tmp_l = tmp_l->next;
            tmp_l->next = new linked_list(data_in);
            tmp_l->next->prev = tmp_l;
        }
    }
    void show(linked_list *start)
    {
        while (start != NULL)
        {
            start->data->show(start->data);
            cout << "  ";
            start = start->next;
        }
    }
    void delete_node(linked_list *&start, int id)
    {
        linked_list<T> *tmp_node = start;
        if (start == NULL)
        {
            cout << "error! empty list.\n";
            return;
        }
        while ((tmp_node->data->get_id(tmp_node->data) != id) && (tmp_node != NULL))
        {
            tmp_node = tmp_node->next;
        }
        if (tmp_node == NULL)
        {
            cout << "error! there is no such node.\n";
            return;
        }
        else if (tmp_node == start)
        {
            cout << "deleted.\n";
            start = start->next;
            if (start == NULL)
                return;
            start->prev = NULL;
            return;
        }
        else if (tmp_node->next == NULL)
        {
            cout << "deleted.\n";
            tmp_node->prev->next = NULL;
            return;
        }
        else
        {
            cout << "deleted.\n";
            tmp_node->prev->next = tmp_node->next;
            tmp_node->next->prev = tmp_node->prev;
            return;
        }
    }
    int search(linked_list *start, int id_in)
    {
        while (start != NULL)
        {
            if (start->get_id(start) == id_in)
                return 1;
            start = start->next;
        }
        return 0;
    }
    int get_id(linked_list *&start_ll)
    {
        return start_ll->data->get_id(start_ll->data);
    }
    T *get_node(linked_list *&start, int id_in)
    {
        linked_list *tmp_ll = start;
        while ((tmp_ll != NULL) && (tmp_ll->get_id(tmp_ll) != id_in))
            tmp_ll = tmp_ll->next;
        if (tmp_ll == NULL)
            return NULL;
        else
            return tmp_ll->data;
    }
};

template <typename T>
class hash_table
{
private:
    int capacity;

public:
    linked_list<T> **array;

    hash_table(int capacity_in)
    {
        array = new linked_list<T> *[capacity_in];
        capacity = capacity_in;
    }
    void insert(hash_table *&start, T *&value)
    {
        if (start == NULL)
        {
            start = new hash_table(10);
        }
        int key_in = value->get_id(value);
        int f_key = start->hash(start, key_in);
        start->array[f_key]->add_node(start->array[f_key], value);
    }
    linked_list<T> *get(hash_table *&start, int key_in)
    {

        int f_key = start->hash(start, key_in);
        linked_list<T> *tmp_ll = start->array[f_key];
        while ((tmp_ll != NULL) && (tmp_ll->get_id(tmp_ll) != key_in))
            tmp_ll = tmp_ll->next;

        return tmp_ll;
    }
    int search(hash_table *&start, int key_in) // not checked, I think this function is not neccessary.
    {
        if (start == NULL)
            return 0;
        int f_key = start->hash(start, key_in);
        linked_list<T> *tmp_T_ll = start->array[f_key];
        if (tmp_T_ll == NULL)
            return 0;
        else
        {
            while ((tmp_T_ll != NULL) && (tmp_T_ll->get_id(tmp_T_ll) != key_in))
                tmp_T_ll = tmp_T_ll->next;
            if (tmp_T_ll != NULL)
                return 1;
            else
                return 0;
        }
    }
    int hash(hash_table *&start, int key_in)
    {
        return (key_in % (start->capacity));
    }
    void delete_member(hash_table *&start, int key_in)
    {
        int f_key = start->hash(key_in);
        linked_list<T> *tmp_T = start->array[f_key];
        if (tmp_T == NULL)
            return;
        else
        {
            tmp_T->delete_node(tmp_T, key_in);
        }
    }
};

class course
{
    // main usage of this class is by objects, not pointers.
private:
    int id;
    string name;
    int capacity;
    int registered_num;

    linked_list<student> *registered_students;
    queue<student> *waiting_list;

public:
    // stack<student> *recycle_bin_student;
    hash_table<course> *course_list;

    course(int id_in, string name_in, int capacity_in)
    {
        id = id_in;
        name = name_in;

        capacity = capacity_in;
        registered_num = 0;

        registered_students = NULL;
        waiting_list = NULL;
        // recycle_bin_student = NULL;

        course_list = NULL;
    }
    void add_node(course *&start_course, course_info *&start_info)
    {
        course *tmp_course = new course(start_info->id, start_info->name, start_info->capacity);
        if (start_course == NULL)
            start_course = new course(-1, "__", 0);

        start_course->course_list->insert(start_course->course_list, tmp_course);
    }
    void register_student(course *&start_course, student *&start_student)
    {
        if (start_course->registered_num >= start_course->capacity)
        {
            start_course->waiting_list->add_node(start_course->waiting_list, start_student);
            cout << "student added to waiting list.\n";
            return;
        }
        else
        {
            start_course->registered_students->add_node(start_course->registered_students, start_student);
            start_course->registered_num += 1;
            cout << "student added.\n";
            return;
        }
    }
    // remained:
    void remove_student(course *&start_course, int id_in)
    {
        student *tmp_student = start_course->registered_students->get_node(start_course->registered_students, id_in);
        start_course->registered_students->delete_node(start_course->registered_students, id_in);
        // start_course->recycle_bin_student->add_node(start_course->recycle_bin_student, tmp_student);
        if (!start_course->waiting_list->is_empty(start_course->waiting_list))
        {
            student *tmp_student2 = start_course->waiting_list->get_node(start_course->waiting_list);
            start_course->registered_students->add_node(start_course->registered_students, tmp_student2);
        }
        else
        {
            start_course->registered_num -= 1;
        }
    }
    void show_registered_students(course *&start_course)
    {
        cout << "\tshowing registered students in the course:";
        if (start_course->registered_students == NULL)
        {
            cout << "\n\t\tno registered student.\n";
            return;
        }
        start_course->registered_students->show(start_course->registered_students);
    }
    void show(course *&start_course)
    {
        cout << "\tcourse info: \n";
        cout << "\tname: " << start_course->name << endl;
        cout << "\tid: " << start_course->id << endl;
        cout << "\tcapacity: " << start_course->capacity << endl;
        cout << "\tregistered: " << start_course->registered_num << endl;
        cout << endl;
    }
    void show_waiting_list(course *&start_course)
    {
        cout << "\tshowing waiting list of the course:\n";
        if (start_course->waiting_list == NULL)
        {
            cout << "\t\tempty waiting list.\n";
            return;
        }
        start_course->waiting_list->show(start_course->waiting_list);
    }
    void show_all_courses(course *&start_course)
    {
        for (int i = 0; i < 10; i++)
        {
            start_course->course_list->array[i]->show(start_course->course_list->array[i]);
        }
        cout << endl
             << endl;
    }
    int get_id(course *&start_course)
    {
        return start_course->id;
    }
};

class student
{
public:
    string name;
    int id;

    linked_list<course> *registered_courses;
    stack<course> *recycle_bin;

public:
    // these two numbers are for undoing registering in a course:
    stack<undo_reg> *tmp_id;     // after registering
    stack<undo_reg> *tmp_id_del; // after deleteing

    hash_table<student> *student_list;

    student(string name_in, int id_in)
    {
        name = name_in;
        id = id_in;

        registered_courses = NULL;
        recycle_bin = NULL;
        student_list = NULL;
    }
    void add_node(student *&start, student_info *&start_info) // this function is for registering new student in system.
    {
        if (start == NULL)
            start = new student("__", -1);
        if (start->student_list->search(start->student_list, start_info->id))
        {
            cout << "\t\terror! this id is already existed.\n";
            return;
        }
        else
        {
            student *tmp_student = new student(start_info->name, start_info->id);
            start->student_list->insert(start->student_list, tmp_student);
        }
    }
    void register_course(student *&start_student, course *&start_course)
    {
        cout << "registering in a course: \n";
        cout << "enter student id: ";
        int student_id_in = -1;
        cin >> student_id_in;
        linked_list<student> *tmp_student_ll = start_student->student_list->get(start_student->student_list, student_id_in);
        student *tmp_student = tmp_student_ll->get_node(tmp_student_ll, student_id_in);
        if (tmp_student == NULL)
        {
            cout << "error! no such student.\n";
            return;
        }

        cout << "showing all courses: " << endl;
        start_course->show_all_courses(start_course);
        cout << endl;
        cout << "enter course id: ";
        int course_id = -1;
        cin >> course_id;
        if (start_student->registered_courses->search(start_student->registered_courses, course_id))
        {
            cout << "error! existed course id.\n";
            return;
        }
        else
        {
            // we have to add student to the course and the course to the student
            linked_list<course> *tmp_ll = start_course->course_list->get(start_course->course_list, course_id);
            course *tmp_course = tmp_ll->get_node(tmp_ll, course_id);
            tmp_course->register_student(tmp_course, tmp_student);
            tmp_student->registered_courses->add_node(tmp_student->registered_courses, tmp_course);

            undo_reg *tmp_undo_reg = new undo_reg(course_id, student_id_in);
            start_student->tmp_id->add_node(start_student->tmp_id, tmp_undo_reg);
        }
    }
    void undo_register_course(student *&start_student, course *&start_course)
    {
        int course_id = -1, student_id = -1;
        undo_reg *tmp_undo_reg = start_student->tmp_id->pop(start_student->tmp_id);
        course_id = tmp_undo_reg->course_id;
        student_id = tmp_undo_reg->student_id;

        linked_list<course> *tmp_course_ll = start_course->course_list->get(start_course->course_list, course_id);
        course *tmp_course = tmp_course_ll->get_node(tmp_course_ll, course_id);

        linked_list<student> *tmp_student_ll = start_student->student_list->get(start_student->student_list, student_id);
        student *tmp_student = tmp_student_ll->get_node(tmp_student_ll, student_id);

        // keep in mind to save it in recycle bin.
        // course:
        tmp_course->remove_student(tmp_course, student_id); // the student will be added to recycle bin.

        // student:
        tmp_student->registered_courses->delete_node(tmp_student->registered_courses, course_id);
        tmp_student->recycle_bin->add_node(tmp_student->recycle_bin, tmp_course);
    }
    // remained:
    void remove_course(student *&start_student, course *&start_course)
    {
        cout << "enter student id: ";
        int student_id = -1;
        cin >> student_id;
        cout << "enter course id to be removed: ";
        int course_id = -1;
        cin >> course_id;

        linked_list<course> *tmp_course_ll = start_course->course_list->get(start_course->course_list, course_id);
        course *tmp_course = tmp_course_ll->get_node(tmp_course_ll, course_id);

        linked_list<student> *tmp_student_ll = start_student->student_list->get(start_student->student_list, student_id);
        student *tmp_student = tmp_student_ll->get_node(tmp_student_ll, student_id);

        // keep in mind to save it in recycle bin.
        // course:
        tmp_course->remove_student(tmp_course, student_id); // the student will be added to recycle bin.

        // student:
        tmp_student->registered_courses->delete_node(tmp_student->registered_courses, course_id);
        // tmp_student->recycle_bin->add_node(tmp_student->recycle_bin, tmp_course);
        undo_reg *tmp_del = new undo_reg(tmp_course->get_id(tmp_course), tmp_student->id);
        start_student->tmp_id_del->add_node(start_student->tmp_id_del, tmp_del);
    }
    void undo_remove(student *&start_student, course *&start_course)
    {
        /*course *tmp_course = start_student->recycle_bin->pop(start_student->recycle_bin);
        student *tmp_student = start_course->recycle_bin_student->pop(start_course->recycle_bin_student);
        // adding student to the course:
        tmp_course->register_student(tmp_course, tmp_student);
        // adding the course to student:
        tmp_student->register_course(tmp_student, tmp_course);*/
        if (start_student->tmp_id_del->is_empty(start_student->tmp_id_del))
        {
            cout << "error! empty stack.\n";
            return;
        }

        undo_reg *tmp_del_nums = start_student->tmp_id_del->pop(start_student->tmp_id_del);
        int course_id = tmp_del_nums->course_id;
        int student_id = tmp_del_nums->student_id;

        linked_list<student> *tmp_student_ll = start_student->student_list->get(start_student->student_list, student_id);
        student *tmp_student = tmp_student_ll->get_node(tmp_student_ll, student_id);

        linked_list<course> *tmp_ll = start_course->course_list->get(start_course->course_list, course_id);
        course *tmp_course = tmp_ll->get_node(tmp_ll, course_id);
        tmp_course->register_student(tmp_course, tmp_student);
        tmp_student->registered_courses->add_node(tmp_student->registered_courses, tmp_course);
    }
    void show_registered_courses(student *&start_student)
    {
        cout << "registered courses: \n";
        start_student->registered_courses->show(start_student->registered_courses);
    }
    int get_id(student *&start_student)
    {
        return start_student->id;
    }
    void show(student *start_student)
    {
        cout << "\tstudent name: " << start_student->name << endl;
        cout << "\tstudent id: " << start_student->id << endl;
        if (start_student->registered_courses == NULL)
        {
            cout << "\t\tno registered courses.\n";
            return;
        }
        start_student->registered_courses->show(start_student->registered_courses);
    }
    void show_student_status(student *&start_student)
    {
        cout << "enter student id: ";
        int student_id = -1;
        cin >> student_id;
        linked_list<student> *tmp_student_list = start_student->student_list->get(start_student->student_list, student_id);
        student *tmp_student = tmp_student_list->get_node(tmp_student_list, student_id);
        start_student->show(tmp_student);
    }
};

class admin
{
private:
    int id;
    string name;

public:
    admin()
    {
    }
    void add_node(admin *&start_admin)
    {
        start_admin = new admin();
        /*
        this part is for getting admin's data from user:
        cout << "enter admin name: ";
        getline(cin, start_admin->name);

        cout << "enter admin id: ";
        cin >> start_admin->id;
        */
        start_admin->name = "ali";
        start_admin->id = 1;
    }
    void add_new_course(admin *&start_admin, course *&start_course, course_info *&start_info)
    {
        start_course->add_node(start_course, start_info);
    }
    void watch_course_status(admin *start_admin, course *&start_course)
    {
        cout << "enter your course id: ";
        int course_id = -1;
        cin >> course_id;

        linked_list<course> *tmp_ll = start_course->course_list->get(start_course->course_list, course_id);
        course *tmp_course = tmp_ll->get_node(tmp_ll, course_id);
        if (tmp_course == NULL)
        {
            cout << "error! no such course.\n";
            return;
        }

        cout << "\n\tcourse status: \n";
        tmp_course->show(tmp_course);
        tmp_course->show_registered_students(tmp_course);
        tmp_course->show_waiting_list(tmp_course);
    }
    void add_student(admin *&start_admin, student *&start_student, student_info *&start_info)
    {
        start_student->add_node(start_student, start_info);
    }
    void watch_studnet_status(admin *&start_admin, student *&start_student)
    {
        cout << "enter student id: ";
        int id_in = -1;
        cin >> id_in;

        linked_list<student> *tmp_student_ll = start_student->student_list->get(start_student->student_list, id_in);
        student *tmp_student = tmp_student_ll->get_node(tmp_student_ll, id_in);
        if (tmp_student == NULL)
        {
            cout << "error! no such student.\n";
            return;
        }
        tmp_student->show(tmp_student);
        cout << "\n\n\n";
    }
    int get_id(admin *&start_admin)
    {
        return start_admin->id;
    }
    void add_student_to_course(admin *&start_admin, student *&start_student, course *&start_course)
    {
        cout << "adding a student to a course by admin:\n";
        start_student->register_course(start_student, start_course);
    }
};

// In bellow, there are some test classes
// to ensure stack, linked_list and hash_table
// classes are written properly.
/*
class test       //testing stack
{
private:
    int data;
    stack<test>* st;
public:
    test(int data_in)
    {
        data=data_in;
        st=NULL;
    }
    void add_node(test*& start_test, int data_in)
    {
        test* tmp_test=new test(data_in);
        if(start_test==NULL)
            start_test=tmp_test;
        start_test->st->add_node(start_test->st, tmp_test);
    }
    void show(test*& start_test)
    {
        while (!start_test->st->is_empty(start_test->st))
        {
            test* popped = start_test->st->pop(start_test->st);
            if (popped != NULL)
                cout << popped->data << "  ";
        }
    }
};
*/
/*
class test       //testing queue
{
private:
    int data;
    queue<test>* tq;
public:
    test(int data_in)
    {
        data=data_in;
        tq=NULL;
    }
    void add_node(test*& start_test, int data_in)
    {
        test* tmp_start=new test(data_in);
        if(start_test==NULL)
            start_test=tmp_start;
        start_test->tq->add_node(start_test->tq, tmp_start);
    }
    void show(test*& start_test)
    {
        while(!start_test->tq->is_empty(start_test->tq))
        {
            cout<<start_test->tq->get_node(start_test->tq)->data<<"  ";
        }
    }
};
*/
/*
class test       //testing linked_list
{
private:
    int data;
    linked_list<test>* ll;
public:
    test(int data_in)
    {
        data=data_in;
        ll=NULL;
    }
    void add_node(test*& start_test, int data_in)
    {
        test* tmp_test=new test(data_in);
        if(start_test==NULL)
            start_test=tmp_test;
        start_test->ll->add_node(start_test->ll, tmp_test);
    }
    void show(test*& start_test)
    {
        linked_list<test>* tmp_ll=start_test->ll;
        while(tmp_ll!=NULL)
        {
            cout<<tmp_ll->data->data<<"  ";
            tmp_ll=tmp_ll->next;
        }
    }
};
*/
/*
class test      // testing hash_table
{
private:
    int data, id;
    hash_table<test> *ht;

public:
    test(int data_in, int id_in)
    {
        data = data_in;
        id = id_in;
        ht = NULL;
    }
    void add_node(test *&start_test, int id_in, int data_in)
    {
        test *tmp_test = new test(data_in, id_in);
        if (start_test == NULL)
            start_test = tmp_test;
        start_test->ht->insert(start_test->ht, tmp_test);
    }
    void show(test *&start_test, int id_in)
    {

        linked_list<test>* tmp_ll=start_test->ht->get(start_test->ht, id_in);
        if(tmp_ll==NULL)
            return;
        cout<<tmp_ll->data->data<<endl;

    }
    int get_id(test *&start_test)
    {
        return start_test->id;
    }
    int get_data(test*& start_test)
    {
        return start_test->data;
    }
    void delete_node(test*& start_test, int id_in)
    {
        start_test->ht->delete_member(start_test->ht, id_in);
    }
};
*/

int main(void)
{
    admin *start_admin = NULL;
    student *start_student = NULL;
    course *start_course = NULL;

    course_info *course_info_p[3];
    string course_name[3] = {"data_structures", "math", "chemistry"};
    int course_id[3] = {1, 2, 3};
    int course_capacity[3] = {4, 3, 2};
    for (int i = 0; i < 3; i++)
        course_info_p[i] = new course_info(course_name[i], course_id[i], course_capacity[i]);

    student_info *student_info_p[10];
    string student_name[10] = {"ali", "sam", "mir", "bad", "amir", "asghar", "hesam", "bahar", "morvarid", "sheida"};
    int student_id[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (int i = 0; i < 10; i++)
        student_info_p[i] = new student_info(student_name[i], student_id[i]);

    // here we make just one admin account:
    start_admin->add_node(start_admin);

    // creating courses:
    for (int i = 0; i < 3; i++)
        start_admin->add_new_course(start_admin, start_course, course_info_p[i]);

    // creating students:
    for (int i = 0; i < 10; i++)
        start_admin->add_student(start_admin, start_student, student_info_p[i]);

    cout << "Hi.\n";
    cout << "In this program, we want to provide an\n";
    cout << "environment to manage registerign students\n";
    cout << "in courses in an imaginary university.\n";
    cout << "some students and courses are added by default,\n";
    cout << "but you can change them in main part of the program.\n\n";

    int operation = -1;
    while (operation != 0)
    {
        cout << "choose mode:  " << "1-admin mode     2-user_mode\n";
        cout << "=> ";
        cin >> operation;
        if (operation == 1)
        {
            cout << "admin mode:" << endl;
            cout << "\tchoose operation:" << endl;

            cout << "\t1-create new course account.\n";
            cout << "\t2-watch course status.\n";
            cout << "\t3-create new student account.\n";
            cout << "\t4-watch student status.\n";
            cout << "\t5-add a student to a course.\n";
            cout << "\t0-exit.\n";
            cout << "\t=> ";

            cin >> operation;

            if (operation == 1)
            {
                cout << "\t\tenter course name: ";
                string tmp_course_name;
                cin >> tmp_course_name;
                cout << "\t\tenter course id: ";
                int tmp_course_id = -1;
                cin >> tmp_course_id;
                cout << "\t\tenter course capacity: ";
                int tmp_course_capacity = -1;
                cin >> tmp_course_capacity;
                course_info *tmp_course_info = new course_info(tmp_course_name, tmp_course_id, tmp_course_capacity);

                start_admin->add_new_course(start_admin, start_course, tmp_course_info);
            }
            else if (operation == 2)
            {
                start_admin->watch_course_status(start_admin, start_course);
            }
            else if (operation == 3)
            {
                cout << "\t\tenter student name: ";
                string tmp_student_name;
                cin >> tmp_student_name;
                cout << "\t\tenter student id: ";
                int tmp_student_id = -1;
                cin >> tmp_student_id;
                student_info_p[0] = new student_info(tmp_student_name, tmp_student_id);
                start_admin->add_student(start_admin, start_student, student_info_p[0]);
            }
            else if (operation == 4)
            {
                start_admin->watch_studnet_status(start_admin, start_student);
            }
            else if (operation == 5)
            {
                start_admin->add_student_to_course(start_admin, start_student, start_course);
            }
            else if (operation == 0)
            {
                ;
            }
            else
            {
                cout << "\t\terror! invalid input." << endl;
            }
        }

        else if (operation == 2)
        {
            cout << "student mode.\n";
            cout << "\tchoose operation:\n";
            cout << "\t1-register in a course.\n";
            cout << "\t2-undo register in a course.\n";
            cout << "\t3-remove a student from a course.\n";
            cout << "\t4-undo remove a student from a course.\n";
            cout << "\t5-show registered courses of a student.\n";
            cout << "\t6-show student status.\n";
            cout << "\t0-exit";
            cout << "=> ";
            cin >> operation;

            if (operation == 1)
            {
                start_student->register_course(start_student, start_course);
            }
            else if (operation == 2)
            {
                start_student->undo_register_course(start_student, start_course);
            }
            else if (operation == 3)
            {
                start_student->remove_course(start_student, start_course);
            }
            else if (operation == 4)
            {
                start_student->undo_remove(start_student, start_course);
            }
            else if (operation == 5)
            {
                start_student->show_registered_courses(start_student);
            }
            else if (operation == 6)
            {

                start_student->show_student_status(start_student);
            }
            else if (operation == 0)
            {
                ;
            }
            else
            {
                cout << "error! invalid input.\n";
            }
        }

        cout << "quit:  0-yes   1-no    ";
        cin >> operation;
    }
    cout << "end of program.\n";
    return 0;
}