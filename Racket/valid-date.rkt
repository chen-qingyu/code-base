#lang racket


(define (leap-year? year)
  #t
  )


(define (valid-date? date)
  (define ht (hash 1 31 2 28 3 31 4 30 5 31 6 30 7 31 8 31 9 30 10 31 11 30 12 31)) ; (hash key1 value1 key2 value2 ...)
  
  (define day (remainder date 100)) ; get remainder of 100
  (define month (remainder (quotient date 100) 100)) ; (quotient 20200930 100) => 202009
  (define year (quotient date 10000)) ; (quotient 20200930 10000) => 2020
  
  (if (leap-year? year)
      (set! ht (hash-set ht 2 29))
      '()
      )
  
  (cond
    [(and
      (and (>= month 1) (<= month 12))
      (and (>= day 1) (<= day (hash-ref ht month)))) ; look-up hash table (hash-ref ht key1)=>value1
     #t]
    [else
     #f]
    )
  )

(valid-date? 20200930); => #t
(valid-date? 20200931); => #f

(valid-date? 20200229); => #t
(valid-date? 20200230); => #f
