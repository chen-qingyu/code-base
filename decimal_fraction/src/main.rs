//! @file main.rs
//! @author 青羽 <236521827@qq.com>
//! @brief 任意进制小数和分数转换系统 demo
//! @version
//!   - v0.1.0 实现十进制循环小数和分数互相转换的功能
//!   - v0.2.0 十进制小数拓展到任意进制小数

use core::str;
use std::io::{self, Write};

use pyinrs::Fraction;
use regex::Regex;

fn main() {
    println!("小数/分数转换系统 demo v0.2.0 by 青羽");
    println!("输入小数，输出分数，反之亦然");
    println!("小数格式：整数部分[.小数部分[~循环节]][#进制]");
    println!("Example: 1, 1.23, 0.~3, 0.24~9, 0.0~0011#2");
    println!("分数格式：分子整数/分母整数");
    println!("Example: 1/2, 1/3, 3/10");
    println!("Ctrl + Z 退出");
    println!();

    print!("> ");
    io::stdout().flush().unwrap();
    while let Some(Ok(line)) = io::stdin().lines().next() {
        if line.contains('/') {
            println!("{}", fraction_to_decimal(&line));
        } else {
            println!("{}", decimal_to_fraction(&line));
        }
        print!("> ");
        io::stdout().flush().unwrap();
    }
    println!("\rGood bye~");
}

fn fraction_to_decimal(line: &str) -> String {
    let f = line.parse::<Fraction>().unwrap();

    if let Some((start, length)) = find_cyclic(f.numerator(), f.denominator()) {
        let s = f64::from(f).to_string();
        format!("{}...", str::from_utf8(&s.as_bytes()[..=(s.find('.').unwrap() + start + length * 3)]).unwrap())
    } else {
        format!("{}", f64::from(f))
    }
}

fn decimal_to_fraction(line: &str) -> String {
    let re_dec = Regex::new(r"^([-+]?\d+)\.?(\d+)?~?(\d+)?#?(\d+)?$").unwrap();
    let caps = re_dec.captures(line).unwrap();
    let base = caps.get(4).map_or(10, |x| x.as_str().parse::<u32>().unwrap());

    let integral = i32::from_str_radix(&caps[1], base).unwrap().abs();
    let decimal = caps.get(2).map(|x| i32::from_str_radix(x.as_str(), base).unwrap());
    let cyclic = caps.get(3).map(|x| i32::from_str_radix(x.as_str(), base).unwrap());

    let is_negative = caps[1].contains('-');
    let base = base as i32;

    // x = c/((base^len(c)-1)*(base^len(d))) = c/(base^len(c+d)-base^len(d))
    let f = match (integral, decimal, cyclic) {
        // 整数
        (i, None, None) => Fraction::from(i),
        // 非循环小数
        (i, Some(d), None) => {
            let decimal_len = caps[2].len() as u32;
            Fraction::from((i * i32::pow(base, decimal_len) + d, i32::pow(base, decimal_len)))
        }
        // 循环小数-无非循环部分
        (i, None, Some(c)) => {
            let cyclic_len = caps[3].len() as u32;
            Fraction::from(i) + Fraction::from((c, i32::pow(base, cyclic_len) - 1))
        }
        // 循环小数-有非循环部分
        (i, Some(d), Some(c)) => {
            let decimal_len = caps[2].len() as u32;
            let cyclic_len = caps[3].len() as u32;
            Fraction::from((i * i32::pow(base, decimal_len) + d, i32::pow(base, decimal_len)))
                + Fraction::from((c, i32::pow(base, cyclic_len + decimal_len) - i32::pow(base, decimal_len)))
        }
    };
    format!("{}", if is_negative { -f } else { f })
}

/// a: 被除数, b: 除数, 返回(循环节起始位置, 循环节长度)
fn find_cyclic(a: i32, b: i32) -> Option<(usize, usize)> {
    if b == 0 {
        panic!("Error: Divide by zero.");
    }

    let mut remainders = Vec::new(); // 存储余数
    let mut remainder = a % b; // 初始余数

    // 检查余数是否开始重复
    while remainder != 0 {
        if remainders.contains(&remainder) {
            // 找到循环节的起始位置
            let start = remainders.iter().position(|r| *r == remainder).unwrap();
            let length = remainders.len() - start;
            return Some((start, length));
        }
        remainders.push(remainder);
        remainder = (remainder * 10) % b; // 左移一位继续迭代
    }

    // 没有找到循环节
    None
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_fraction_to_decimal() {
        assert_eq!(fraction_to_decimal("1/2"), "0.5");
        assert_eq!(fraction_to_decimal("1/3"), "0.333...");
        assert_eq!(fraction_to_decimal("1/30"), "0.0333...");
        assert_eq!(fraction_to_decimal("5/6"), "0.8333...");
        assert_eq!(fraction_to_decimal("83/99"), "0.838383...");
        assert_eq!(fraction_to_decimal("123/1000"), "0.123");
        assert_eq!(fraction_to_decimal("123/999"), "0.123123123...");
        assert_eq!(fraction_to_decimal("123/1"), "123");
        assert_eq!(fraction_to_decimal("187/1665"), "0.1123123123...");
        assert_eq!(fraction_to_decimal("61111/4950"), "12.34565656...");

        assert_eq!(fraction_to_decimal("-1/-1"), "1");
        assert_eq!(fraction_to_decimal("19/-10"), "-1.9");
        assert_eq!(fraction_to_decimal("-1/3"), "-0.333...");
        assert_eq!(fraction_to_decimal("1/-9"), "-0.111...");
    }

    #[test]
    fn test_decimal_to_fraction() {
        assert_eq!(decimal_to_fraction("0.5"), "1/2");
        assert_eq!(decimal_to_fraction("0.~3"), "1/3"); // 0.333...
        assert_eq!(decimal_to_fraction("0.0~3"), "1/30"); // 0.0333...
        assert_eq!(decimal_to_fraction("0.8~3"), "5/6"); // 0.8333...
        assert_eq!(decimal_to_fraction("0.~83"), "83/99"); // 0.838383...
        assert_eq!(decimal_to_fraction("0.123"), "123/1000");
        assert_eq!(decimal_to_fraction("0.~123"), "41/333"); // 0.123123123...
        assert_eq!(decimal_to_fraction("123"), "123");
        assert_eq!(decimal_to_fraction("0.1~123"), "187/1665"); // 0.1123123123...
        assert_eq!(decimal_to_fraction("12.34~56"), "61111/4950"); // 12.34565656...
        assert_eq!(decimal_to_fraction("0.24~9"), "1/4"); // 0.24999... = 0.25
        assert_eq!(decimal_to_fraction("0.~375"), "125/333"); // 0.375375375...
        assert_eq!(decimal_to_fraction("4.~518"), "122/27"); // 4.518518518...
        assert_eq!(decimal_to_fraction("0.~9"), "1"); // 0.999... = 1

        assert_eq!(decimal_to_fraction("-1"), "-1");
        assert_eq!(decimal_to_fraction("-0.~1"), "-1/9"); // -0.111...
        assert_eq!(decimal_to_fraction("-1.9"), "-19/10");
        assert_eq!(decimal_to_fraction("-1.~9"), "-2"); // -1.999... = -2
        assert_eq!(decimal_to_fraction("-1.1~9"), "-6/5"); // -1.1999... = -1.2

        assert_eq!(decimal_to_fraction("11"), "11"); // 11
        assert_eq!(decimal_to_fraction("11#10"), "11"); // 11(10) = 11(10)
        assert_eq!(decimal_to_fraction("11#2"), "3"); // 11(2) = 3(10)
        assert_eq!(decimal_to_fraction("11#16"), "17"); // 11(16) = 17(10)
        assert_eq!(decimal_to_fraction("0.1#2"), "1/2"); // 0.1(2) = 0.5(10)
        assert_eq!(decimal_to_fraction("0.0~0011#2"), "1/10"); // 0.0001100110011...(2) = 0.1(10)
        assert_eq!(decimal_to_fraction("-0.0~0011#2"), "-1/10"); // -0.0001100110011...(2) = -0.1(10)
        assert_eq!(decimal_to_fraction("0.~1#2"), "1"); // 0.111...(2) = 0.999...(10) = 1
    }
}
