
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
  call void @fo()
  ret i32 0
}

define void @fo() {
fo_entry:
  %pog = alloca [10 x [10 x i8]], align 1
  %i = alloca i32, align 4
  %int_const = alloca i32, align 4
  store i32 10, ptr %int_const, align 4
  %readString_arg = load i32, ptr %int_const, align 4
  call void @readString(i32 %readString_arg, ptr %pog)
  call void @writeString(ptr %pog)
  ret void
}
