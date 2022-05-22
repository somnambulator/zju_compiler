; ModuleID = 'Code Gen'
source_filename = "Code Gen"

@strtype = external global [256 x i8]
@A = internal global [625 x i32] zeroinitializer, align 4
@B = internal global [625 x i32] zeroinitializer, align 4
@C = internal global [625 x i32] zeroinitializer, align 4
@readfomat = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@readfomat.1 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@readfomat.2 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@readfomat.3 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@readfomat.4 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@printfomat = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@readfomat.5 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@printfomat.6 = private unnamed_addr constant [5 x i8] c"%d%s\00", align 1
@printfomat.7 = private unnamed_addr constant [5 x i8] c"%d%s\00", align 1

define void @main() {
entry:
  %k = alloca i32, align 4
  %j = alloca i32, align 4
  %i = alloca i32, align 4
  %size_B = alloca i32, align 4
  %size_A = alloca i32, align 4
  %BN = alloca i32, align 4
  %BM = alloca i32, align 4
  %AN = alloca i32, align 4
  %AM = alloca i32, align 4
  store i32 0, i32* %AM, align 4
  store i32 0, i32* %AN, align 4
  store i32 0, i32* %BM, align 4
  store i32 0, i32* %BN, align 4
  store i32 0, i32* %size_A, align 4
  store i32 0, i32* %size_B, align 4
  store i32 0, i32* %i, align 4
  store i32 0, i32* %j, align 4
  store i32 0, i32* %k, align 4
  %readtmp = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @readfomat, i32 0, i32 0), i32* %AM)
  %readtmp1 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @readfomat.1, i32 0, i32 0), i32* %AN)
  %AM2 = load i32, i32* %AM, align 4
  %AN3 = load i32, i32* %AN, align 4
  %multmp = mul i32 %AM2, %AN3
  store i32 %multmp, i32* %size_A, align 4
  store i32 0, i32* %i, align 4
  br label %loop

loop:                                             ; preds = %afterloop, %entry
  %loopentry = phi i32 [ 0, %entry ], [ 0, %afterloop ]
  store i32 0, i32* %j, align 4
  br label %loop4

loop4:                                            ; preds = %loop4, %loop
  %loopentry5 = phi i32 [ 0, %loop ], [ 0, %loop4 ]
  %j6 = load i32, i32* %j, align 4
  %i7 = load i32, i32* %i, align 4
  %addtmp = add i32 %i7, 0
  %multmp8 = mul i32 25, %addtmp
  %addtmp9 = add i32 %j6, %multmp8
  %arrayele = getelementptr inbounds i32, i32* getelementptr inbounds ([625 x i32], [625 x i32]* @A, i32 0, i32 0), i32 %addtmp9
  %readtmp10 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @readfomat.2, i32 0, i32 0), i32* %arrayele)
  %j11 = load i32, i32* %j, align 4
  %addtmp12 = add i32 %j11, 1
  store i32 %addtmp12, i32* %j, align 4
  %j13 = load i32, i32* %j, align 4
  %AN14 = load i32, i32* %AN, align 4
  %cmptmp = icmp slt i32 %j13, %AN14
  %loopcond = icmp ne i1 %cmptmp, false
  br i1 %loopcond, label %loop4, label %afterloop

afterloop:                                        ; preds = %loop4
  %i15 = load i32, i32* %i, align 4
  %addtmp16 = add i32 %i15, 1
  store i32 %addtmp16, i32* %i, align 4
  %i17 = load i32, i32* %i, align 4
  %AM18 = load i32, i32* %AM, align 4
  %cmptmp19 = icmp slt i32 %i17, %AM18
  %loopcond20 = icmp ne i1 %cmptmp19, false
  br i1 %loopcond20, label %loop, label %afterloop21

afterloop21:                                      ; preds = %afterloop
  %readtmp22 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @readfomat.3, i32 0, i32 0), i32* %BM)
  %readtmp23 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @readfomat.4, i32 0, i32 0), i32* %BN)
  %AN24 = load i32, i32* %AN, align 4
  %BM25 = load i32, i32* %BM, align 4
  %cmptmp26 = icmp ne i32 %AN24, %BM25
  %ifcond = icmp ne i1 %cmptmp26, false
  br i1 %ifcond, label %then, label %else

then:                                             ; preds = %afterloop21
  %0 = alloca [256 x i8], i64 ptrtoint ([256 x i8]* getelementptr ([256 x i8], [256 x i8]* null, i32 1) to i64), align 1
  %strtmp = getelementptr [256 x i8], [256 x i8]* %0, i32 0
  store [256 x i8] c"Incompatible Dimensions\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00", [256 x i8]* %strtmp, align 1
  %printtmp = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @printfomat, i32 0, i32 0), [256 x i8]* %0)
  br label %ifcont

else:                                             ; preds = %afterloop21
  br label %ifcont

ifcont:                                           ; preds = %else, %then
  %iftmp = phi i32 [ 0, %then ], [ 0, %else ]
  store i32 0, i32* %i, align 4
  br label %loop27

loop27:                                           ; preds = %afterloop44, %ifcont
  %loopentry28 = phi i32 [ 0, %ifcont ], [ 0, %afterloop44 ]
  store i32 0, i32* %j, align 4
  br label %loop29

loop29:                                           ; preds = %loop29, %loop27
  %loopentry30 = phi i32 [ 0, %loop27 ], [ 0, %loop29 ]
  %j31 = load i32, i32* %j, align 4
  %i32 = load i32, i32* %i, align 4
  %addtmp33 = add i32 %i32, 0
  %multmp34 = mul i32 25, %addtmp33
  %addtmp35 = add i32 %j31, %multmp34
  %arrayele36 = getelementptr inbounds i32, i32* getelementptr inbounds ([625 x i32], [625 x i32]* @B, i32 0, i32 0), i32 %addtmp35
  %readtmp37 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @readfomat.5, i32 0, i32 0), i32* %arrayele36)
  %j38 = load i32, i32* %j, align 4
  %addtmp39 = add i32 %j38, 1
  store i32 %addtmp39, i32* %j, align 4
  %j40 = load i32, i32* %j, align 4
  %BN41 = load i32, i32* %BN, align 4
  %cmptmp42 = icmp slt i32 %j40, %BN41
  %loopcond43 = icmp ne i1 %cmptmp42, false
  br i1 %loopcond43, label %loop29, label %afterloop44

afterloop44:                                      ; preds = %loop29
  %i45 = load i32, i32* %i, align 4
  %addtmp46 = add i32 %i45, 1
  store i32 %addtmp46, i32* %i, align 4
  %i47 = load i32, i32* %i, align 4
  %BM48 = load i32, i32* %BM, align 4
  %cmptmp49 = icmp slt i32 %i47, %BM48
  %loopcond50 = icmp ne i1 %cmptmp49, false
  br i1 %loopcond50, label %loop27, label %afterloop51

afterloop51:                                      ; preds = %afterloop44
  store i32 0, i32* %i, align 4
  br label %loop52

loop52:                                           ; preds = %afterloop105, %afterloop51
  %loopentry53 = phi i32 [ 0, %afterloop51 ], [ 0, %afterloop105 ]
  store i32 0, i32* %j, align 4
  br label %loop54

loop54:                                           ; preds = %afterloop98, %loop52
  %loopentry55 = phi i32 [ 0, %loop52 ], [ 0, %afterloop98 ]
  %j56 = load i32, i32* %j, align 4
  %i57 = load i32, i32* %i, align 4
  %addtmp58 = add i32 %i57, 0
  %multmp59 = mul i32 25, %addtmp58
  %addtmp60 = add i32 %j56, %multmp59
  %arrayele61 = getelementptr inbounds i32, i32* getelementptr inbounds ([625 x i32], [625 x i32]* @C, i32 0, i32 0), i32 %addtmp60
  store i32 0, i32* %arrayele61, align 4
  store i32 0, i32* %k, align 4
  br label %loop62

loop62:                                           ; preds = %loop62, %loop54
  %loopentry63 = phi i32 [ 0, %loop54 ], [ 0, %loop62 ]
  %j64 = load i32, i32* %j, align 4
  %i65 = load i32, i32* %i, align 4
  %addtmp66 = add i32 %i65, 0
  %multmp67 = mul i32 25, %addtmp66
  %addtmp68 = add i32 %j64, %multmp67
  %arrayele69 = getelementptr inbounds i32, i32* getelementptr inbounds ([625 x i32], [625 x i32]* @C, i32 0, i32 0), i32 %addtmp68
  %j70 = load i32, i32* %j, align 4
  %i71 = load i32, i32* %i, align 4
  %addtmp72 = add i32 %i71, 0
  %multmp73 = mul i32 25, %addtmp72
  %addtmp74 = add i32 %j70, %multmp73
  %arrayele75 = getelementptr inbounds i32, i32* getelementptr inbounds ([625 x i32], [625 x i32]* @C, i32 0, i32 0), i32 %addtmp74
  %arrayElementValue = load i32, i32* %arrayele75, align 4
  %k76 = load i32, i32* %k, align 4
  %i77 = load i32, i32* %i, align 4
  %addtmp78 = add i32 %i77, 0
  %multmp79 = mul i32 25, %addtmp78
  %addtmp80 = add i32 %k76, %multmp79
  %arrayele81 = getelementptr inbounds i32, i32* getelementptr inbounds ([625 x i32], [625 x i32]* @A, i32 0, i32 0), i32 %addtmp80
  %arrayElementValue82 = load i32, i32* %arrayele81, align 4
  %j83 = load i32, i32* %j, align 4
  %k84 = load i32, i32* %k, align 4
  %addtmp85 = add i32 %k84, 0
  %multmp86 = mul i32 25, %addtmp85
  %addtmp87 = add i32 %j83, %multmp86
  %arrayele88 = getelementptr inbounds i32, i32* getelementptr inbounds ([625 x i32], [625 x i32]* @B, i32 0, i32 0), i32 %addtmp87
  %arrayElementValue89 = load i32, i32* %arrayele88, align 4
  %multmp90 = mul i32 %arrayElementValue82, %arrayElementValue89
  %addtmp91 = add i32 %arrayElementValue, %multmp90
  store i32 %addtmp91, i32* %arrayele69, align 4
  %k92 = load i32, i32* %k, align 4
  %addtmp93 = add i32 %k92, 1
  store i32 %addtmp93, i32* %k, align 4
  %k94 = load i32, i32* %k, align 4
  %AN95 = load i32, i32* %AN, align 4
  %cmptmp96 = icmp slt i32 %k94, %AN95
  %loopcond97 = icmp ne i1 %cmptmp96, false
  br i1 %loopcond97, label %loop62, label %afterloop98

afterloop98:                                      ; preds = %loop62
  %j99 = load i32, i32* %j, align 4
  %addtmp100 = add i32 %j99, 1
  store i32 %addtmp100, i32* %j, align 4
  %j101 = load i32, i32* %j, align 4
  %BN102 = load i32, i32* %BN, align 4
  %cmptmp103 = icmp slt i32 %j101, %BN102
  %loopcond104 = icmp ne i1 %cmptmp103, false
  br i1 %loopcond104, label %loop54, label %afterloop105

afterloop105:                                     ; preds = %afterloop98
  %i106 = load i32, i32* %i, align 4
  %addtmp107 = add i32 %i106, 1
  store i32 %addtmp107, i32* %i, align 4
  %i108 = load i32, i32* %i, align 4
  %AM109 = load i32, i32* %AM, align 4
  %cmptmp110 = icmp slt i32 %i108, %AM109
  %loopcond111 = icmp ne i1 %cmptmp110, false
  br i1 %loopcond111, label %loop52, label %afterloop112

afterloop112:                                     ; preds = %afterloop105
  store i32 0, i32* %i, align 4
  br label %loop113

loop113:                                          ; preds = %afterloop148, %afterloop112
  %loopentry114 = phi i32 [ 0, %afterloop112 ], [ 0, %afterloop148 ]
  store i32 0, i32* %j, align 4
  br label %loop115

loop115:                                          ; preds = %ifcont140, %loop113
  %loopentry116 = phi i32 [ 0, %loop113 ], [ 0, %ifcont140 ]
  %j117 = load i32, i32* %j, align 4
  %BN118 = load i32, i32* %BN, align 4
  %subtmp = sub i32 %BN118, 1
  %cmptmp119 = icmp ne i32 %j117, %subtmp
  %ifcond120 = icmp ne i1 %cmptmp119, false
  br i1 %ifcond120, label %then121, label %else130

then121:                                          ; preds = %loop115
  %j122 = load i32, i32* %j, align 4
  %i123 = load i32, i32* %i, align 4
  %addtmp124 = add i32 %i123, 0
  %multmp125 = mul i32 25, %addtmp124
  %addtmp126 = add i32 %j122, %multmp125
  %arrayele127 = getelementptr inbounds i32, i32* getelementptr inbounds ([625 x i32], [625 x i32]* @C, i32 0, i32 0), i32 %addtmp126
  %arrayelement = load i32, i32* %arrayele127, align 4
  %1 = alloca [256 x i8], i64 ptrtoint ([256 x i8]* getelementptr ([256 x i8], [256 x i8]* null, i32 1) to i64), align 1
  %strtmp128 = getelementptr [256 x i8], [256 x i8]* %1, i32 0
  store [256 x i8] c" \00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00", [256 x i8]* %strtmp128, align 1
  %printtmp129 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @printfomat.6, i32 0, i32 0), i32 %arrayelement, [256 x i8]* %1)
  br label %ifcont140

else130:                                          ; preds = %loop115
  %j131 = load i32, i32* %j, align 4
  %i132 = load i32, i32* %i, align 4
  %addtmp133 = add i32 %i132, 0
  %multmp134 = mul i32 25, %addtmp133
  %addtmp135 = add i32 %j131, %multmp134
  %arrayele136 = getelementptr inbounds i32, i32* getelementptr inbounds ([625 x i32], [625 x i32]* @C, i32 0, i32 0), i32 %addtmp135
  %arrayelement137 = load i32, i32* %arrayele136, align 4
  %2 = alloca [256 x i8], i64 ptrtoint ([256 x i8]* getelementptr ([256 x i8], [256 x i8]* null, i32 1) to i64), align 1
  %strtmp138 = getelementptr [256 x i8], [256 x i8]* %2, i32 0
  store [256 x i8] c"\0A\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00", [256 x i8]* %strtmp138, align 1
  %printtmp139 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @printfomat.7, i32 0, i32 0), i32 %arrayelement137, [256 x i8]* %2)
  br label %ifcont140

ifcont140:                                        ; preds = %else130, %then121
  %iftmp141 = phi i32 [ 0, %then121 ], [ 0, %else130 ]
  %j142 = load i32, i32* %j, align 4
  %addtmp143 = add i32 %j142, 1
  store i32 %addtmp143, i32* %j, align 4
  %j144 = load i32, i32* %j, align 4
  %BN145 = load i32, i32* %BN, align 4
  %cmptmp146 = icmp slt i32 %j144, %BN145
  %loopcond147 = icmp ne i1 %cmptmp146, false
  br i1 %loopcond147, label %loop115, label %afterloop148

afterloop148:                                     ; preds = %ifcont140
  %i149 = load i32, i32* %i, align 4
  %addtmp150 = add i32 %i149, 1
  store i32 %addtmp150, i32* %i, align 4
  %i151 = load i32, i32* %i, align 4
  %AM152 = load i32, i32* %AM, align 4
  %cmptmp153 = icmp slt i32 %i151, %AM152
  %loopcond154 = icmp ne i1 %cmptmp153, false
  br i1 %loopcond154, label %loop113, label %afterloop155

afterloop155:                                     ; preds = %afterloop148
  ret void
}

declare i32 @scanf(i8*, ...)

declare i32 @printf(i8*, ...)
