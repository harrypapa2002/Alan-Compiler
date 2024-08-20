
@global_str = private unnamed_addr constant [3 x i8] c", \00", align 1
@global_str.2 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@global_str.3 = private unnamed_addr constant [16 x i8] c"Initial array: \00", align 1
@global_str.4 = private unnamed_addr constant [15 x i8] c"Sorted array: \00", align 1

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
  %seed = alloca i32, align 4
  %x = alloca [16 x i32], align 4
  %y = alloca [10 x i8], align 1
  %i = alloca i32, align 4
  store i32 65, ptr %seed, align 4
  store i32 0, ptr %i, align 4
  br label %cond

cond:                                             ; preds = %loop, %main_entry
  %left_load = load i32, ptr %i, align 4
  %lttmp = icmp slt i32 %left_load, 16
  %0 = zext i1 %lttmp to i32
  %while_cond = icmp ne i32 %0, 0
  br i1 %while_cond, label %loop, label %afterloop

loop:                                             ; preds = %cond
  %left_load1 = load i32, ptr %seed, align 4
  %multmp = mul i32 %left_load1, 137
  %addtmp = add i32 %multmp, 220
  %right_load = load i32, ptr %i, align 4
  %addtmp2 = add i32 %addtmp, %right_load
  %modtmp = srem i32 %addtmp2, 101
  store i32 %modtmp, ptr %seed, align 4
  %load_rvalue = load i32, ptr %seed, align 4
  %load_index = load i32, ptr %i, align 4
  %elementptr = getelementptr [16 x i32], ptr %x, i32 0, i32 %load_index
  store i32 %load_rvalue, ptr %elementptr, align 4
  %left_load3 = load i32, ptr %i, align 4
  %addtmp4 = add i32 %left_load3, 1
  store i32 %addtmp4, ptr %i, align 4
  br label %cond

afterloop:                                        ; preds = %cond
  call void @writeArray(ptr @global_str.3, i32 16, ptr %x)
  call void @bsort(i32 16, ptr %x)
  call void @writeArray(ptr @global_str.4, i32 16, ptr %x)
  ret void
}

define void @bsort(i32 %n, ptr %x) {
bsort_entry:
  %n1 = alloca i32, align 4
  store i32 %n, ptr %n1, align 4
  %x2 = alloca ptr, align 8
  store ptr %x, ptr %x2, align 8
  %changed = alloca i8, align 1
  %i = alloca i32, align 4
  store i8 121, ptr %changed, align 1
  br label %cond

cond:                                             ; preds = %afterloop, %bsort_entry
  %left_load = load i8, ptr %changed, align 1
  %eqtmp = icmp eq i8 %left_load, 121
  %0 = zext i1 %eqtmp to i32
  %while_cond = icmp ne i32 %0, 0
  br i1 %while_cond, label %loop, label %afterloop24

loop:                                             ; preds = %cond
  store i8 110, ptr %changed, align 1
  store i32 0, ptr %i, align 4
  br label %cond3

cond3:                                            ; preds = %ifcont, %loop
  %left_load4 = load i32, ptr %n1, align 4
  %subtmp = sub i32 %left_load4, 1
  %left_load5 = load i32, ptr %i, align 4
  %lttmp = icmp slt i32 %left_load5, %subtmp
  %1 = zext i1 %lttmp to i32
  %while_cond6 = icmp ne i32 %1, 0
  br i1 %while_cond6, label %loop7, label %afterloop

loop7:                                            ; preds = %cond3
  %load_index = load i32, ptr %i, align 4
  %x_arrayptr = load ptr, ptr %x2, align 8
  %elementptr = getelementptr i32, ptr %x_arrayptr, i32 %load_index
  %left_load8 = load i32, ptr %elementptr, align 4
  %addtmp = add i32 %left_load8, 1
  %left_load9 = load i32, ptr %i, align 4
  %addtmp10 = add i32 %left_load9, 1
  %x_arrayptr11 = load ptr, ptr %x2, align 8
  %elementptr12 = getelementptr i32, ptr %x_arrayptr11, i32 %addtmp10
  %left_load13 = load i32, ptr %elementptr12, align 4
  %addtmp14 = add i32 %left_load13, 1
  %gttmp = icmp sgt i32 %addtmp, %addtmp14
  %2 = zext i1 %gttmp to i32
  %if_cond = icmp ne i32 %2, 0
  br i1 %if_cond, label %then, label %else

then:                                             ; preds = %loop7
  %load_index15 = load i32, ptr %i, align 4
  %x_arrayptr16 = load ptr, ptr %x2, align 8
  %elementptr17 = getelementptr i32, ptr %x_arrayptr16, i32 %load_index15
  %left_load18 = load i32, ptr %i, align 4
  %addtmp19 = add i32 %left_load18, 1
  %x_arrayptr20 = load ptr, ptr %x2, align 8
  %elementptr21 = getelementptr i32, ptr %x_arrayptr20, i32 %addtmp19
  call void @swap(ptr %elementptr17, ptr %elementptr21)
  store i8 121, ptr %changed, align 1
  br label %ifcont

else:                                             ; preds = %loop7
  br label %ifcont

ifcont:                                           ; preds = %else, %then
  %left_load22 = load i32, ptr %i, align 4
  %addtmp23 = add i32 %left_load22, 1
  store i32 %addtmp23, ptr %i, align 4
  br label %cond3

afterloop:                                        ; preds = %cond3
  br label %cond

afterloop24:                                      ; preds = %cond
  ret void
}

define void @swap(ptr %x, ptr %y) {
swap_entry:
  %x1 = alloca ptr, align 8
  store ptr %x, ptr %x1, align 8
  %y2 = alloca ptr, align 8
  store ptr %y, ptr %y2, align 8
  %t = alloca i32, align 4
  %x_load = load ptr, ptr %x1, align 8
  %load_rvalue = load i32, ptr %x_load, align 4
  store i32 %load_rvalue, ptr %t, align 4
  %y_load = load ptr, ptr %y2, align 8
  %load_rvalue3 = load i32, ptr %y_load, align 4
  %x_load4 = load ptr, ptr %x1, align 8
  store i32 %load_rvalue3, ptr %x_load4, align 4
  %load_rvalue5 = load i32, ptr %t, align 4
  %y_load6 = load ptr, ptr %y2, align 8
  store i32 %load_rvalue5, ptr %y_load6, align 4
  ret void
}

define void @writeArray(ptr %msg, i32 %n, ptr %x) {
writeArray_entry:
  %msg1 = alloca ptr, align 8
  store ptr %msg, ptr %msg1, align 8
  %n2 = alloca i32, align 4
  store i32 %n, ptr %n2, align 4
  %x3 = alloca ptr, align 8
  store ptr %x, ptr %x3, align 8
  %i = alloca i32, align 4
  %msg_load = load ptr, ptr %msg1, align 8
  call void @writeString(ptr %msg_load)
  store i32 0, ptr %i, align 4
  br label %cond

cond:                                             ; preds = %ifcont, %writeArray_entry
  %left_load = load i32, ptr %i, align 4
  %right_load = load i32, ptr %n2, align 4
  %lttmp = icmp slt i32 %left_load, %right_load
  %0 = zext i1 %lttmp to i32
  %while_cond = icmp ne i32 %0, 0
  br i1 %while_cond, label %loop, label %afterloop

loop:                                             ; preds = %cond
  %left_load4 = load i32, ptr %i, align 4
  %gttmp = icmp sgt i32 %left_load4, 0
  %1 = zext i1 %gttmp to i32
  %if_cond = icmp ne i32 %1, 0
  br i1 %if_cond, label %then, label %else

then:                                             ; preds = %loop
  call void @writeString(ptr @global_str)
  br label %ifcont

else:                                             ; preds = %loop
  br label %ifcont

ifcont:                                           ; preds = %else, %then
  %load_index = load i32, ptr %i, align 4
  %x_arrayptr = load ptr, ptr %x3, align 8
  %elementptr = getelementptr i32, ptr %x_arrayptr, i32 %load_index
  %writeInteger_arg = load i32, ptr %elementptr, align 4
  call void @writeInteger(i32 %writeInteger_arg)
  %left_load5 = load i32, ptr %i, align 4
  %addtmp = add i32 %left_load5, 1
  store i32 %addtmp, ptr %i, align 4
  br label %cond

afterloop:                                        ; preds = %cond
  call void @writeString(ptr @global_str.2)
  ret void
}
