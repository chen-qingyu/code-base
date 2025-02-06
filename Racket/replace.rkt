#lang racket/base

(require racket/trace)


;; Find the index of the substring in the string from index start, else #f.
(define (find-string str sub #:optional (start 0))
  (let ((sub-len (string-length sub)))
    (let loop ((i start))
      (if (<= (+ i sub-len) (string-length str))
          (if (equal? (substring str i (+ i sub-len)) sub)
              i
              (loop (+ i 1)))
          #f))))


;; Replace the first occurrence of the substring from index start.
(define (replace-first str old new #:optional (start 0))
  (let ((next (find-string str old #:optional start)))
    (if next
        (string-append
         (substring str 0 next)
         new
         (substring str (+ next (string-length old))))
        str)))


;; Replace the occurrences of the substring.
(define (replace str old new)
  (let ((next (find-string str old)))
    (if next
        (replace (replace-first str old new #:optional next) old new)
        str)))


(trace replace)
(replace "tests: a test string with test substring" "test" "sample")
