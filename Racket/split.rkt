#lang racket/base

(require rackunit)


;; Find the index for the pattern in text from index start, else -1.
(define (kmp-search text pattern start)
  (let ((n (- (string-length text) start))
        (m (string-length pattern)))
    ; compute partial match table
    (define (make-match-table)
      (let ((table (make-vector m 0)))
        (let loop ((i 1) (j 0))
          (cond
            ((= i m) table)
            ((eq? (string-ref pattern i) (string-ref pattern j))
             (vector-set! table i (+ j 1))
             (loop (+ i 1) (+ j 1)))
            ((= j 0) (vector-set! table i 0) (loop (+ i 1) 0))
            (else (loop i (vector-ref table (- j 1))))))))
    ; search
    (define (search str)
      (if (> m n)
          -1 ; 如果模式串比文本还长,直接返回
          (let ((table (make-match-table)))
            (let loop ((i 0) (j 0) (matches -1))
              (cond
                ((= j m) (- i m)) ; 匹配完成,记录起始位置
                ((= i n) matches) ; 文本结束,返回匹配结果
                ((eq? (string-ref str i) (string-ref pattern j))
                 (loop (+ i 1) (+ j 1) matches)) ; 字符匹配,继续比较
                ((= j 0) (loop (+ i 1) 0 matches)) ; j 回到 0, i 向前移动
                (else (loop i (vector-ref table (- j 1)) matches))))))) ; 根据部分匹配表回退 j
    (let ((pos (search (substring text start))))
      (if (= pos -1) -1 (+ pos start)))))


(check-equal? (kmp-search "hello" "l" 0) 2)
(check-equal? (kmp-search "hello" "l" 2) 2)
(check-equal? (kmp-search "hello" "l" 4) -1)
(check-equal? (kmp-search "hello" "me" 0) -1)
(check-equal? (kmp-search "helllllllo" "helllllllo" 0) 0)
(check-equal? (kmp-search "helllllllo" "helllllllo" 1) -1)
(check-equal? (kmp-search "abxabcabcaby" "abcaby" 0) 6)
(check-equal? (kmp-search "abxabcabcaby" "abcaby" 2) 6)


;; Split string.
(define (split str sep)
  (let ((sep-len (string-length sep)))
    ; tail recursive auxiliary function
    (define (split-helper start acc)
      (let ((next (kmp-search str sep start)))
        (if (not (= next -1))
            (split-helper (+ next sep-len) (cons (substring str start next) acc))
            (cons (substring str start) acc))))
    ; call tail recursion
    (if (zero? sep-len)
        (map string (string->list str))
        (reverse (split-helper 0 '())))))


(check-equal? (split "one, two, three" ", ") '("one" "two" "three"))
(check-equal? (split "192.168.0.1" ".") '("192" "168" "0" "1"))
(check-equal? (split "hello world!" " ") '("hello" "world!"))
(check-equal? (split "aaa" "") '("a" "a" "a"))
(check-equal? (split "hello world!" "hello world!") '("" ""))
(check-equal? (split "hello world!" "!") '("hello world" ""))
(check-equal? (split "aaa" "a") '("" "" "" ""))
(check-equal? (split " " " ") '("" ""))
