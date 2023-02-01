# ft_containers

**What is ft_containers?**

This project is about re-impelementing a few container types of the C++ standard template library:

| Container_name	  | Description |
|:------------------|:-----------------------------------------------------------------|
| [std::stack](http://www.cplusplus.com/reference/stack/stack) | Type of container adaptor, specifically designed to operate in a LIFO context (last-in first-out), where elements are inserted and extracted only from one end of the container |
| [std::vector](http://www.cplusplus.com/reference/vector/vector) | Container which stores elements of a given type in a linear arrangement, has dynamic memory management, and allows fast random access to any element |
| [std::map](http://www.cplusplus.com/reference/map/map) | An associative containers that store elements formed by a combination of a key value and a mapped value, following a specific order |
| [std::set](http://www.cplusplus.com/reference/set/set) | Set is a container that store unique elements following a specific order. Stored elements must be unique and cannot be modified once it is stored in the set |



**Requirements:**
- `ft:map` and `ft::set` must be implemented using [self ordering Red-Black binary search tree](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree)
- [std::allocator](https://en.cppreference.com/w/cpp/memory/allocator) must be used
- it is mandatory to implement:</br>
&nbsp;&nbsp; - [std::iterator_traits](https://en.cppreference.com/w/cpp/iterator/iterator_traits) </br>
&nbsp;&nbsp; - [std::reverse_iterator](https://en.cppreference.com/w/cpp/iterator/reverse_iterator) </br>
&nbsp;&nbsp; - [std::enable_if](https://en.cppreference.com/w/cpp/types/enable_if) </br>
&nbsp;&nbsp; - [std::is_integral](https://en.cppreference.com/w/cpp/types/is_integral) </br>
&nbsp;&nbsp; - [std::equal](https://en.cppreference.com/w/cpp/algorithm/equal) and/or [std::lexicographical_compare](https://en.cppreference.com/w/cpp/algorithm/lexicographical_compare) </br>
&nbsp;&nbsp; - [std::pair](https://en.cppreference.com/w/cpp/utility/pair) </br>
&nbsp;&nbsp; - [std::make_pair](https://en.cppreference.com/w/cpp/utility/pair/make_pair) </br>
- Code must be written according C++98 standard
- Everything must compile with the flags -Wall -Wextra -Werror

**Project related documents:**
- [Subject pdf](https://github.com/VMiseikis/42-Course/blob/master/Subject%20PDFs/ft_containers.en.subject.pdf) </br>

## Sources
- [C++ reference](https://en.cppreference.com/w/)
- [How to write an STL compatible container](https://medium.com/@vgasparyan1995/how-to-write-an-stl-compatible-container-fc5b994462c6)
- [What is Allocator](https://medium.com/@vgasparyan1995/what-is-an-allocator-c8df15a93ed)
- [Type traits](https://www.codeproject.com/Articles/774841/Cplusplus-type-traits-Header)
- [Templates](https://www.codeproject.com/Articles/257589/An-Idiots-Guide-to-Cplusplus-Templates-Part-1)
- [Custom Iterators](https://anderberg.me/2016/07/04/c-custom-iterators/)
- [Custom iterators in modern C++](https://www.internalpointers.com/post/writing-custom-iterators-modern-cpp)
- [Iterator traits](https://www.codeproject.com/Articles/36530/An-Introduction-to-Iterator-Traits)
- [SFINAE and enable_if](https://eli.thegreenplace.net/2014/sfinae-and-enable_if/)
- [Red-Black Binary Tree](https://www.youtube.com/watch?v=4KDovab_OS8&t=938s)
- [Red-Black Binary Tree examples](https://www.youtube.com/watch?v=PgO_Xj7DC1A)

## Grading:
<div align="center">
<img width="150" alt="" src="https://github.com/VMiseikis/42-Course/blob/master/Images/Score%20125:100.png">
</div>
