# Theory

This file contains explanations of each theory bullet point that is captured in the [2025 Bachelor Degree Exam Theory](https://www.cs.ubbcluj.ro/wp-content/uploads/TematicaInformatica_2025_Ro.pdf).

## Programming and Algorithmic

Covers **Basis of Programming**, **Object Oriented Programming** and **Data Structures and Algorithms** courses.

1. **Searching Algorithms**

   1.1. **Sequential Search**: linearly pass a collection to find a key such that a[i] == k, i=1,n;

   2.1. **Binary Search**: supposing you have an ordered collection; we can check for the existence of an element in `O(log(n))` time, passing a tree like structure;

    ```python
    def sequential_search(collection, key) ->     bool:
        for i in range(len(collection)):
            if collection[i] == key:
                return True
        return False
    
    # suppose 0-indexing and collection is sorted     in ascending order
    def binary_search(collection, key, start, end) -> bool:
        if start >= end - 1:
            if len(collection) == 0:
                return False
            
            return True if (collection[start] == key) else False
        
        midpoint = start + (end - start) // 2
    
        if collection[midpoint] == key:
            return True
        if collection[midpoint] < key:
            return binary_search(collection, key, start, midpoint)
        return binary_search(collection, key, midpoint, end)
    ```

2. **Merging**: an algorithm that is capable of merging two sorted lists, giving a sorted list as a result;

   ```python
   # assuming ascending order for both methods

   def merge_iterative(l1, l2) -> list:
        i, j = 0, 0

        l = []
        while i < len(l1) and j < len(l2):
            if l1[i] < l2[j]:
                l.append(l1[i])
                i += 1
            else:
                l.append(l2[j])
                j += 1

        while i < len(l1):
            l.append(l1[i])
            i += 1
        
        while j < len(l2):
            l.append(l2[j])
            j += 1
        
        return l
    
    # indexL1, indexL2 = len(l1) - 1, len(l2) - 1
    # constructs the merged list going from end to the beginning,
    # by adding the bigger element to the sorted list that is called recursively
    def merge_recursive(l1, l2, indexL1, indexL2) -> list:
        if indexL1 < 0 and indexL2 < 0:
            return []
        elif indexL1 >= 0 and indexL2 < 0:
            return merge_recursive(l1, l2, indexL1 - 1, indexL2) + l1[indexL1]
        elif indexL1 < 0 and indexL2 >= 0:
            return merge_recursive(l1, l2, indexL1, indexL2 - 1) + l2[indexL2]
        
        if l1[indexL1] < l2[indexL2]:
            return merge_recursive(l1, l2, indexL1, indexL2 - 1) + l2[indexL2]
        
        return merge_recursive(l1, l2, indexL1 - 1, indexL2) + l1[indexL1]
    ```

3. **Sorting**: algorithms capable of sorting collections;

    3.1. **Bubble Sort**: compares adjacent elements and swaps them if they are out of order;

    ```python
    def bubble_sort(collection) -> list:
        is_sorted = False
        result = [x for x in collection]
        while not is_sorted:
            is_sorted = True
            for i in range(len(result) - 1):
                if result[i] > result[i + 1]:
                    result[i], result[i + 1] = result[i + 1], result[i]
                    is_sorted = False

        return result
    ```

    3.2. **Insertion Sort**: puts the element in its correct position in the sorted list;

    ```python
    def insertion_sort(collection) -> list:
        result = [x for x in collection]

        for i in range(1, len(result)):
            # taking the current element and the index before it
            j, elem = i - 1, result[i]

            # comparing with the index before the element until
            # we reach the element's position
            while j > 0 and elem < result[j]:
                result[j+1] = result[j]
            
            # now we have the correct position of the element
            result[j+1] = elem
        
        return result
    ```

    3.3. **Selection Sort**: compares the current element with the ones after it, ensuring that it will be positioned correctly in the list;

    ```python
    def selection_sort(collection) -> list:
        result = [x for x in collection]

        for i in range(len(result) - 1):
            for j in range(i + 1, len(result)):
                if result[i] > result[j]:
                    result[i], result[j] = result[j], result[i]
        
        return result     
    ```

    3.4. **Merge Sort**: divide and conquer algorithm; splits the list and merges the results;

    ```python
    def merge_sort(collection, start, end) -> list:
        if start >= end - 1:
            return collection[start:end]
        
        midpoint = start + (end - start) // 2
        left = merge_sort(collection, start, midpoint)
        right = merge_sort(collection, midpoint, right)
        
        return merge(left, right)
    ```

    3.5. **Quicksort**: divide and conquer algorithm; sorts the elements in a collection based on a pivot, such that _the elements left to the pivot are lower than the pivot_, and _the elements right to the pivot are greater than the pivot_;

    ```python
    def quicksort(collection, start, end) -> list:
        if start >= end or start < 0:
            return collection
        
        p = partition(collection, start, end)

        quicksort(collection, start, p)
        quicksort(collection, p+1, end)
        return collection
    
    def partition(collection, start, end):
        i, pivot = start, collection[end - 1]

        for j in range(start, end - 1):
            if piv > a[j]:
                a[i], a[j] = a[j], a[i]
                i += 1
            
        a[i], a[end - 1] = a[end - 1], a[i]
        return i
    ```

4. **Backtracking**: collection of algorithms that find all the solutions of a given problem;

    ```python
    # checks if the current solution is indeed a correct solution of our problem
    def is_solution(current_solution):
        ...

    # checks if the current_solution can drive us to a correct solution of our problem
    def candidate(current_solution):
        ...

    # traverses the solution space, adding elements and checks if they are viable solutions or not
    def backtracking(solution_space, current_solution):
        ...
    ```

5. **Algorithmic complexity**:
    - O = `upper-bound`, Theta = `exact`, Omega = `lowerbound`;
    - T(n) = k * T(n - 1) + constant = most algorithms
    - T(n) = k * T(n / p) + constant = recursive; here we write n as p^k;

6. **OOP**: classes and objects, class members and methods;
    - **access specifiers**:
        - `public`: access from wherever;
        - `protected`: access by the class and its inheritors;
        - `private`: access only within the class (and friends C++);
        - `static`: can be accessed without needing to instantiate a class object (is subordinated to the above access specifiers);
    - **constructors**, **destructors**;
    - **inheritance**, **function overriding**, **polymorphism**, **dynamic binding (with virtual in C++)**, **abstract classes (abstract keyword or pure virtual functions in C++) and interfaces**;

7. **UML Diagrams**:
    - **clear diamond**: aggregation, whole-part relationship, the part can logically be in other wholes and can exist separate from the whole;
        - example: members of a student club;
    - **filled diamond**: composition, whole-part relationship, the part can not logically be in other wholes and cannot exist separate from the whole:
        - example: living species organs;
    - *: 0 or more,
    - 0..m: 0 or maximum m;
    - left to right, up to bottom;

8. **Data Structures**
    - Lists: homogenous data structure, contiguous searching space;

        ```text
        List<T>, ArrayList<T> in Java, List<T> in C#, [] in Python, std:vector<T> or std::list<T> in C++
        ```

    - Dictionaries: data structure that holds key:value pairs, useful for fast lookup;

        ```text
        Map<K, V>, HashMap<K, V> in Java, Dictionary<K, V> in C#, {} in Python, std::map<k, v> or std::unordered_map<k, v> in C++

        Also, we can consider sets as dictionaries:

        Set<T>, HashSet<T> in Java, HashSet<T> in C#, set() in Python, std::set<T> in C++
        ```

    - Binary Search Trees: data structure useful to hold sorted data;
        - _left < root < right_;
        - **Traversals**:
            - preorder traversal: root -> left -> right;
            - postorder traversal: left -> right -> root;
            - inorder traversal: left -> root -> right **GIVES SORTED COLLECTION**;

    - HashTable: the data structure used to implement dictionaries, holds key value pairs, with keys put in buckets by a mathematical function that gives an unique position in the table;

## Databases

Covers the `Databases` course.

1. **Relationships**: a relation can be seen as a set R = [A1, A2, ..., An], where A_i is an attribute of a given relation;
    - example: Student[CodStudent, NameStudent, PhoneStudent]

2. **Integrity Constraints**: ensures that we only have legal instances that are well structured and do not produce anomalies or redundancies. They are applied all instances of the relationship;
    - **Domain Constraints**: applies to the domain of an attribute (e.g. price is a real positive number etc.);
    - **Key Contrains**: some fields can be used to uniquely identify all attributes of a given instance (e.g. the CNP of a Person);
    - **External Key Constrains**: used for referencing keys from other relationships (e.g. Courses retains an external key to the Teacher that holds the course);

3. **SQL Syntax** - not going to write it here, there are docs;

4. **Functional dependencies**: two sets of attributes `A, B from R` are in a functional dependency `A -> B` if for all unique values of the set of attributes A, we can uniquely identify the attributes in the set of attributes B;
    - A functionally determines B;
    - B is functionally dependent of A;
    - e.g.: if a Person's CNP is present in multiple files, they should point to the same Person attributes;

5. **Keys**:
    - **Primary Key**: a set of attributes chosen for uniquelly identifying the attributes of any instance;
    - **Candidate Key**: a set of attributes that are not part of the **Primary Key**, but can still be used to uniquelly identify the attributes of any instance;
    - **Superkey**: a set of attributes that contains a **Key**;

6. **Normal Forms**: techniques used to further escape from redundancy and insertion/update/deletion anomalies;
    - **1NF**: the attributes of a relationship can only take atomic values (from the definition of the Relational Model);
    - **2NF**: the functional dependencies are given by the whole key;
        - there are no **_partial dependencies_** or **_dependencies_** between non-key attributes;
    - **3NF**: the functional dependencies are given exclusively by the key, **_except for prime attributes, which can depend on non-key attributes_**;
        - we can have a key attribute that depends on a non-key attribute, but we cannot have a non-key attribute that depends on another non-key attribute;
    - **BCNF**: stronger **3NF**, the dependencies are given **ONLY** by the key;

## Operating Systems

Covers the **Operating Systems** course.

1. **Unix Filesystem**: **everything is a file**;
    - the filesystem is structured as follows:
        - block 0 = boot block, where the OS starts itself;
        - block 1 = superblock, magic numbers, such as the sizes of the disk and other metadata;
        - block 2..n = i-nodes, structures that hold information about the files;
        - block n..m = blocks, real data that is transferred between the OS, RAM and disk;
    - an **inode** holds the following information:
        - name: the name of the file;
        - link_count: the number of references to the file (hard or soft);
        - size: the total size of the file;
        - user_id: ID of the owner of the file;
        - group_id: ID of the group of the owner of the file;
        - permissions: the permissions of the file;
        - access_time: last timestamp of the file access;
        - mod_time: last timestamp of the file permission update;
        - inode_time: last timestamp of the modification of the inode structure;
        - block_list: list of direct accesible blocks;
        - inode_list: list of addresses that contain addresses to other blocks;
    - a block can be accessed in the following ways:
        - direct access: we have the address of the block;
        - indirect access: access to an array that holds addresses to other blocks;
        - 2-indirect access: access to an array that holds addresses to an array that contains addreses to other blocks;
        - 3-indirect access: array of addresses to 2-indirect access;
    - **hard-link**: the file is doubled as if `cp` was called, the OS will see two identical files in two separate places, link_count increases;
    - **soft-link**: special file that contains a reference to the linked file, modifying the target file will break the link;
    - **TYPES OF FILES**:
        - Regular file;
        - Directory;
        - Block peripheral: references other disks or storages (SSD, hard-disk, cards etc.); stored in `/mnt`;
        - Character peripheral: files that process streams of data (keyboard, mouse etc.); stored in `/dev`;
        - Socket: communcation primitive for computers at distance;
        - Hard-link;
        - Symbolic-link;
        - FIFO;
        ---------------
        - PIPE;
        - Shared memory segments;
        - Message queues;
        - Semaphores;
    - _**!!!**_ the file doesn't get deleted until link_count reaches 0; link_count only increments on **hard-links**, **soft-links** only reference the file;

2. **Processes** - programs launched in execution;
    - have their own memory management, own lifetime;
    - are expensive, useful for computational expensive tasks (use threads for simple functionalities);
    - `fork()`: creates a new child process, transferring the existing context of the parent to the child, then they both resume their execution from the next instruction;
        - -1: if the fork() fails;
        - 0: in child, use getpid() to get its PID;
        - pid_child; in parent, the PID of the newly created child;
    - `exec*`: launches a new program in execution;
        - `execl, execle, execlp`: specifies the path to the program, arguments in variadic form (list) terminated by NULL, and can inherit the environment from the existing process or not, and can be searched in PATH or not;
        - `execv, execvp, execvpe`: specifies the path of the program, arguments in a char*[] array of NULL terminated strings (C-strings), and can inherit the environment from the existing process or not, and can be searched in PATH or not;
        - _**!!!**_ the first argument of the argument list should be the name of the program to execute (by convention)
    - `pid_t wait(int* status), pid_t waitpid(pid_t p_child, int* status, int options)`: waits for a child process to change its state;
        - -1: error, errno=ECHILD if there are no children left;
        - pid_child: the PID of the child that changed its status;
    - `int pipe(int p[2])`: creates a uni-directional Pipe communcation channel, which by default is open on both-ends, the programmer needing to ensure that it remains uni-directional;
    - `int mkfifo(const char* path, int perms)`: creates a FIFO at the specified path, with the specified permissions;
    - _**!!!**_ not going to explain how open, close, read, write work, there are manuals for this;

3. **Shell Programming**
    - **Predefined Bash Variables**:
        - `$0`: name of the program:
        - `$1..$9`: first 9 arguments;
        - `$*` list of arguments, `"$*"` arguments as a whole string;
        - `$@` list of arguments, `"$@"` arguments as separate strings;
        - `@?` last command exit code;
    - **Shell Code Flow Structures**:

        ```console
        (commands)
        {commands}
        
        if commands; then commands [elif commands; then commands]* [else commands] fi
        
        case word in pattern1;; commands pattern2;; commands ... patternn ... commands;; esac

        for name; do commands; done

        for name in [word]+; do commands; done

        while commands; do commands; done

        until commands; do commands; done

        |   - pipe linking
        &&  - andTrue, || - orFalse
        <, << - input redirects: replace and append
        >, >> - output redirects: replace and append

        2>&1        - duplicates the stdout file descriptor (&) and redirects stderr there
        1>/dev/null - /dev/null deletes any input, so this can be used to delete any input

        (command substitution)
        `command` or $(command) - executes a command and returns its result

        (arithmetic evaluation)
        $((command)) - evaluates the command in arithmetic, like expr
        ```

    - **Regular Expressions**:
        - `*`: any amount of times;
        - `?`: 0 or 1 times;
        - `+`: at least one time;
        - `\[a-z\]`: one character from the a-z sequence;
        - `\[^a-z\]`: any character that is not in the a-z sequence;
        - `^, $`: start and end of line;
        - `\b, \\<\\>`: word boundaries;
        - `\d, \w, \s`: digits, characters, whitespaces;
        - `(group)`: groups characters together;
        - `c`: the c character;

    - **grep**: `grep -Eqvinr pattern1\npattern2 \[file|directory\]`
        - `-E`: POSIX Extended Regex;
        - `-q`: quiet, only return code of success/failure;
        - `-v`: inverted match;
        - `-i`: insensitive case match;
        - `-n`: line number of line matched;
        - `-r`: search recursively in directories;
    - **sed**: stream editor, `sed -E command file`
        - `-E`: POSIX Extended Regex;
        - `command`:
            - `<ADDRESS>d`: deletes lines at the specified address, which can be `/REGEX/`, `LINE`, `addr1,addr2`;
            - `s/<PATTERN1>/<PATTERN2>/[gi]`: substitute PATTERN1 with PATTERN2 only on the first match
                - `g`: global subsitution, change all occurences;
                - `i`: case insensitive match;
            - `y/SET1/SET2`: translation table, SET1, SET2 need to be the same size, one-to-one-mapping, always global;
    - **Other Shell Commands**: use `man` to find them, i've only listed some of them here;
        - `cat`: concatenates contents of all passed files;
        - `chmod -R [ugoa][+-=][perms]`: changes permissions of files, recursively if the file is a directory or link and `-R` is present;
            - `u, g, o, a` = `user, group, others, all`, specifies for which set of users to apply the permissions; default is `all (a)`;
            - `perms` can be either one of `u,g,o` or multiple of `rwxXst`, or `octal representation (600, 777 etc.)`, where each digit represents a set of users in `u, g, o` order;
        - `cut [-d <delim_char> -f <range_of_fields>] file`: selects only a subsequence of fields from the tokens delimited by delim_char;
        - `find <starting_point> -name <name> -type <filetype>`: finds all files from a givne starting point, with name matching or filetype matching(`fdbcpls`);
        - `head/tail [-n [+]number] file`: takes the first/last number lines from a file;
            - if `+` is present, then all lines are taken except for the `last/first number-1 lines`;
        - `read [-p command] file`: reads data from a file or stdin;
            - `-p`: use the output of command as prompt;
        - `wc [-w -c -l] file(s)`: returns the number of newline counts, words and byte counts;
            - the output will be split in:

            ```console
            lines words characters file1
            lines words characters file2
            ...
            lines words characters filen
            lines words characters total
            ```

            - `-w`: word counts;
            - `-c`: character (byte) counts;
            ` `-l`: newline counts;
        - `test [EXPRESSION]`: checks for condition;
            - `-b/-c/-f/-d/-r/-w/-x/-s FILE: type of file, permissions or information about its size;
            - `FILE1 -nt FILE2`: FILE1 newer than FILE2?
            - `FILE1 -ot FILE2`: FILE1 older than FILE2?
            - `FILE1 -ef FILE2`: are FILE1 and FILE2 the same file?
            - `-z STRING`: is STRING empty?
            - `-n STRING`: is STRING not empty?
            - `STRING1 = STRING2`: are the two strings equal?
            - `STRING1 != STRING2`: are the two strings not equal?
            - `EXPR1 -a EXPR2`: is EXPR1 and EXPR2 true?
            - `EXPR1 -o EXPR2`: is EXPR1 or EXPR2 true?
            - `! EXPR`: is EXPR false?
            - `(EXPR)`: groups expressions together;
            - `NUMBER1 -eq NUMBER2`: are the two numbers equal?
            - `NUMBER1 -ne NUMBER2`: are the two numbers not equal?
            - `NUMBER1 -lt NUMBER2`: is NUMBER1 less than NUMBER2?
            - `NUMBER1 -le NUMBER2`: is NUMBER1 less than or equal to NUMBER
            - `NUMBER1 -gt NUMBER2`: is NUMBER1 greater than NUMBER2?
            - `NUMBER1 -ge NUMBER2`: is NUMBER1 greater than or equal to NUMBER2?
