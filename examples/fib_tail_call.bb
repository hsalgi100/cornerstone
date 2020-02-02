; https://www.geeksforgeeks.org/print-fibonacci-sequence-using-2-variables/

(include "cornerstone/lib/core.bb")

(def @fib_ (params (%a u64) (%b u64) (%i u64) (%top u64)) void (do

    (if (== %i %top) (do (return-void)))

    (call @u64.println (args (+ %a %b)))
    
    (let %new-b (+ %a %b))
    (call-tail @fib_ (args (- %new-b %a) %new-b (+ %i 1) %top))
    (return-void)
))

; b = a + old_b 
; a = a + old_b - a


(def @fib (params (%n u64)) void (do
    (if (>= %n 0) (do
        (call @u64.println (args 0))
    ))

    (if (>= %n 1) (do 
        (call @u64.println (args 1))
    ))

    (call @fib_ (args 0 1 2 (+ %n 1)))
    (return-void)
))

(def @main params i32 (do
    (call @fib (args 10000))
    (return 0)
))