(set-logic QF_UF)
(set-option :produce-stats true)
(set-option :stats-out "stats.out")
(declare-sort U 0)
(declare-fun c15 () U)
(declare-fun c17 () U)
(declare-fun c11 () U)
(declare-fun f5 (U U) U)
(declare-fun c10 () U)
(declare-fun c16 () U)
(declare-fun c_0 () U)
(declare-fun c_1 () U)
(declare-fun c_2 () U)
(declare-fun c_3 () U)
(assert
 (let (
 (?v_123 (f5 c_0 c_3))
 (?v_135 (f5 c_2 c_1))
 )

(and (distinct c_0 c_1 c_2 c_3)
 (or (= (f5 c_2 c_1) c_0)
 (= (f5 c_2 c_1) c_1)
 (= (f5 c_2 c_1) c_2)
 (= (f5 c_2 c_1) c_3))
 (or true (= (f5 c_3 c_3) c_3))
 (or (= c15 c_1) (= c15 c_2) (= c15 c_3))
 (or (= c17 c_0) (= c17 c_1) (= c17 c_2) (= c17 c_3))
 (or (= c11 c_0) (= c11 c_1) (= c11 c_2) (= c11 c_3)) 
 (or (= c10 c_0) (= c10 c_3))
 (or (= c16 c_2) (= c16 c_3)))))
(check-sat)
(exit)
