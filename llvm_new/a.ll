
declare void @writeInteger(i32)

declare void @writeByte(i8)

declare void @writeChar(i8)

declare void @writeString(ptr)

declare i32 @readInteger()

declare i8 @readByte()

declare i8 @readChar()

declare void @readString(i32, ptr)

declare i32 @extend(i8)

declare i8 @shrink(i32)

declare i32 @strlen(ptr)

declare i32 @strcmp(ptr, ptr)

declare void @strcpy(ptr, ptr)

declare void @strcat(ptr, ptr)

define i32 @main() {
entry:
  call void @foo()
  ret i32 0
}

define void @foo() {
foo_entry:
  %str_const_alloca = alloca [8 x i8], align 1
  %0 = getelementptr [8 x i8], ptr %str_const_alloca, i32 0, i32 0
  store i8 34, ptr %0, align 1
  %1 = getelementptr [8 x i8], ptr %str_const_alloca, i32 0, i32 1
  store i8 102, ptr %1, align 1
  %2 = getelementptr [8 x i8], ptr %str_const_alloca, i32 0, i32 2
  store i8 111, ptr %2, align 1
  %3 = getelementptr [8 x i8], ptr %str_const_alloca, i32 0, i32 3
  store i8 111, ptr %3, align 1
  %4 = getelementptr [8 x i8], ptr %str_const_alloca, i32 0, i32 4
  store i8 92, ptr %4, align 1
  %5 = getelementptr [8 x i8], ptr %str_const_alloca, i32 0, i32 5
  store i8 110, ptr %5, align 1
  %6 = getelementptr [8 x i8], ptr %str_const_alloca, i32 0, i32 6
  store i8 34, ptr %6, align 1
  %7 = getelementptr [8 x i8], ptr %str_const_alloca, i32 0, i32 7
  store i8 0, ptr %7, align 1
  call void @writeString(ptr %str_const_alloca)
  ret void
}
