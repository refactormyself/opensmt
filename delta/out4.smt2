(set-logic QF_UF)
(declare-sort S0 0)
(declare-fun v0 () S0)
(declare-fun v1 () S0)
(declare-fun v2 () S0)
(declare-fun v3 () S0)
(declare-fun v4 () S0)
(declare-fun f0 (S0) S0)
(declare-fun f1 (S0 S0 S0) S0)
(declare-fun f2 (S0 S0 S0) S0)
(declare-fun p3 (S0 S0 S0) Bool)
(assert
 (let ((e6 (f0 v0)))
 (let ((e7 (f2 v0 v0 v0)))
 (let ((e13 (f0 v0)))
 (let ((e14 (f2 e6 v0 v0)))
 (let ((e17 (f1 e13 v4 v0)))
 (let ((e19 (f1 e13 e17 e13)))
 (let ((e20 (f1 v1 v4 e13)))
 (let ((e22 (f1 v0 v1 e6)))
 (let ((e47 (ite false e6 v0)))
 (let ((e51 (ite false v0 e20)))
 (let ((e54 (ite false v1 e47)))
 (let ((e56 (ite false e51 e7)))
 (let ((e59 (ite false e17 e7)))
 (let ((e66 (ite false e6 e54)))
 (let ((e86 (p3 e22 e56 e19)))
 (let ((e87 (distinct e14 v0)))
 (let ((e90 (p3 e59 e19 e7)))
 (let ((e92 (distinct e66 v2)))
 (let ((e135 (not e92)))
 (let ((e137 (=> e86 false)))
 (let ((e148 (or e90 false)))
 (let ((e174 (ite e135 false false)))
 (let ((e175 (ite e148 false false)))
 (let ((e179 (or e87 e174)))
 (let ((e183 (and e137 e175)))
 (let ((e184 (xor e183 e179)))
 e184)))))))))))))))))))))))))))
(check-sat)

