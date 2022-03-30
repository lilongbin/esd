@startuml
Title "stream类图"
abstract class ios_Base
abstract class ios
abstract class istream
abstract class ostream


ios_Base <|-- ios
ios <|-- istream
ios <|-- ostream

istream <|-- iostream
ostream <|-- iostream

istream <|-- ifstream
istream <|-- istringstream
ostream <|-- ofstream
ostream <|-- ostringstream
iostream <|-- fstream
iostream <|-- stringstream

istringstream <|-- stringbuf
ostringstream <|-- stringbuf
stringstream <|-- stringbuf


ifstream <|-- filebuf
ofstream <|-- filebuf
fstream <|-- filebuf


abstract class streambuf
streambuf <|-- stringbuf
streambuf <|-- filebuf

@enduml


```sequence
张三->李四: 嘿，小四儿, 写博客了没?
Note right of 李四: 李四愣了一下，说：
李四-->张三: 忙得吐血，哪有时间写。
```

```sequence
Andrew->China: Says Hello
Note right of China: China thinks\nabout it
China-->Andrew: How are you?
Andrew->>China: I am good thanks!
```

```sequence
Title: Here is a title
A->B: Normal line
B-->C: Dashed line
C->>D: Open arrow
D-->>A: Dashed open arrow

Note left of A: Note to the\n left of A
Note right of A: Note to the\n right of A
Note over A: Note over A
Note over C,D: Note over both C and D
```

```flow
st=>start: 开始
e=>end: 结束
op=>operation: 我的操作
cond=>condition: 确认？

st->op->cond
cond(yes)->e
cond(no)->op
```
