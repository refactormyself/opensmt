(set-logic QF_UF)
(declare-fun x () Bool)
(assert x)
(check-sat)
(push 1)
(assert (not x))
(check-sat)
(pop 1)
(check-sat)
(declare-fun y () Bool)
(assert (or (not x) y))
(push 1)
(check-sat)
