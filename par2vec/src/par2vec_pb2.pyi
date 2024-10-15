from google.protobuf.internal import containers as _containers
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Iterable as _Iterable, Optional as _Optional

DESCRIPTOR: _descriptor.FileDescriptor

class HelloRequest(_message.Message):
    __slots__ = ("hello",)
    HELLO_FIELD_NUMBER: _ClassVar[int]
    hello: str
    def __init__(self, hello: _Optional[str] = ...) -> None: ...

class HelloReply(_message.Message):
    __slots__ = ("reply",)
    REPLY_FIELD_NUMBER: _ClassVar[int]
    reply: str
    def __init__(self, reply: _Optional[str] = ...) -> None: ...

class Par2VecRequest(_message.Message):
    __slots__ = ("paragraph",)
    PARAGRAPH_FIELD_NUMBER: _ClassVar[int]
    paragraph: str
    def __init__(self, paragraph: _Optional[str] = ...) -> None: ...

class DefaultReply(_message.Message):
    __slots__ = ("dim", "fVec")
    DIM_FIELD_NUMBER: _ClassVar[int]
    FVEC_FIELD_NUMBER: _ClassVar[int]
    dim: int
    fVec: _containers.RepeatedScalarFieldContainer[float]
    def __init__(self, dim: _Optional[int] = ..., fVec: _Optional[_Iterable[float]] = ...) -> None: ...
