;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-lambda-reader.ss" "lang")((modname d-n) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
;; n is the base, m is the power, and k is the base of sum

;; (d-n) get the last digit of
;; [n^m + (factorial k) + (factorial (k+1)) + ... + (factorial m)]

;; d-n: Num Num Num -> Num
(define (d-n n m k)
  (local
    ;; (first-term) calculate first term of n
    ;; first-term: Num Num -> Num
    [(define (first-term n m)
       (expt n m))

     ;; (second-term-helper) list out every number that will be calculated in second term
     ;; second-term-helper: Num Num -> (listof Num)
     (define (second-term-helper m k)
       (cond
         [(= k (+ 1 m)) empty]
         [else (cons k (second-term-helper m (+ k 1)))]))

     ;; (new-num) calculate (n*(n-1)...*1) for a num
     ;; new-num: Num -> Num
     (define (new-num n)
       (cond
         [(= 0 n) 1]
         [else (* n (new-num (- n 1)))]))

     ;; (second-term-helper2) generate the factorialized list
     ;; secon-term-helper2: (listof Num) -> (listof Num)
     (define (second-term-helper2 l)
       (map (lambda (x) (new-num x)) l))

     ;; (second-term) calculate the sum of every number in factorialized list
     ;; secon-term: (listof Num) -> Num
     (define (second-term l)
       (cond
         [(empty? l) 0]
         [else (+ (first l) (second-term (rest l)))]))

     ;; (sum) get the sum of two terms
     ;; sum: Num Num Num -> Num
     (define (sum n m k)
       (cond
         [(> k m) "m should be >= k"]
         [else (+ (first-term n m) (second-term (second-term-helper2 (second-term-helper m k))))]))

     ;; (num-to-list) transform the summed number to a list
     ;; num-to-list: Num -> (listof Num)
     (define (num-to-list n)
       (map string->number
            (map list->string
                 (map (lambda (l) (cons l empty))
                      (string->list (number->string n))))))

     ;; (last-digit) gets the last digit of the list
     ;; last-digit: Num -> Num
     (define (last-digit x)
       (cond
         [(number? x) (string->number
                       (substring (number->string x)
                                  (- (length (num-to-list x)) 1) (length (num-to-list x))))]
         [else  "m should be >= k"]))]
    (last-digit (sum n m k))))
