
%reverse_closure = type { ptr }
%innerIncrement_closure = type { ptr }

@global_str = private unnamed_addr constant [23 x i8] c"y in innerIncrement = \00", align 1
@global_str.2 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@global_str.3 = private unnamed_addr constant [16 x i8] c"y in reverse = \00", align 1
@global_str.4 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@global_str.5 = private unnamed_addr constant [37 x i8] c"y in reverse after innerIncrement = \00", align 1
@global_str.6 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@global_str.7 = private unnamed_addr constant [13 x i8] c"y in main = \00", align 1
@global_str.8 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@global_str.9 = private unnamed_addr constant [27 x i8] c"y in main after reverse = \00", align 1
@global_str.10 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1

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
  call void @main.1()
  ret i32 0
}

define void @main.1() {
main_entry:
  %y = alloca i32, align 4
  store i32 0, ptr %y, align 4
  call void @writeString(ptr @global_str.7)
  %writeInteger_arg = load i32, ptr %y, align 4
  call void @writeInteger(i32 %writeInteger_arg)
  call void @writeString(ptr @global_str.8)
  %reverse_closure_instance = alloca %reverse_closure, align 8
  %y_ptr = getelementptr inbounds %reverse_closure, ptr %reverse_closure_instance, i32 0, i32 0
  store ptr %y, ptr %y_ptr, align 8
  call void @reverse(ptr %reverse_closure_instance)
  call void @writeString(ptr @global_str.9)
  %writeInteger_arg1 = load i32, ptr %y, align 4
  call void @writeInteger(i32 %writeInteger_arg1)
  call void @writeString(ptr @global_str.10)
  ret void
}

define void @reverse(ptr %closure) {
reverse_entry:
  %y_ptr = getelementptr inbounds %reverse_closure, ptr %closure, i32 0, i32 0
  %y = load ptr, ptr %y_ptr, align 8
  %y1 = alloca ptr, align 8
  store ptr %y, ptr %y1, align 8
  %y_load = load ptr, ptr %y1, align 8
  store i32 5, ptr %y_load, align 4
  call void @writeString(ptr @global_str.3)
  %y_load2 = load ptr, ptr %y1, align 8
  %writeInteger_arg = load i32, ptr %y_load2, align 4
  call void @writeInteger(i32 %writeInteger_arg)
  call void @writeString(ptr @global_str.4)
  %innerIncrement_closure_instance = alloca %innerIncrement_closure, align 8
  %y_ptr3 = getelementptr inbounds %innerIncrement_closure, ptr %innerIncrement_closure_instance, i32 0, i32 0
  %y_load4 = load ptr, ptr %y1, align 8
  store ptr %y_load4, ptr %y_ptr3, align 8
  call void @innerIncrement(ptr %innerIncrement_closure_instance)
  call void @writeString(ptr @global_str.5)
  %y_load5 = load ptr, ptr %y1, align 8
  %writeInteger_arg6 = load i32, ptr %y_load5, align 4
  call void @writeInteger(i32 %writeInteger_arg6)
  call void @writeString(ptr @global_str.6)
  ret void
}

define void @innerIncrement(ptr %closure) {
innerIncrement_entry:
  %y_ptr = getelementptr inbounds %innerIncrement_closure, ptr %closure, i32 0, i32 0
  %y = load ptr, ptr %y_ptr, align 8
  %y1 = alloca ptr, align 8
  store ptr %y, ptr %y1, align 8
  %y_load = load ptr, ptr %y1, align 8
  %left_load = load i32, ptr %y_load, align 4
  %addtmp = add i32 %left_load, 1
  %y_load2 = load ptr, ptr %y1, align 8
  store i32 %addtmp, ptr %y_load2, align 4
  call void @writeString(ptr @global_str)
  %y_load3 = load ptr, ptr %y1, align 8
  %writeInteger_arg = load i32, ptr %y_load3, align 4
  call void @writeInteger(i32 %writeInteger_arg)
  call void @writeString(ptr @global_str.2)
  ret void
}
