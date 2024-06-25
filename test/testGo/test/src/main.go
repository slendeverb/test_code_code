package main

import (
	"fmt"
	"math"
)

func main() {
	var number float32 = 0.0625
	bits := math.Float32bits(number) // 打印出32位数据的二进制表示。
	binary := fmt.Sprintf("%.32b", bits)
	fmt.Printf("Bit Pattern: %s | %s %s | %s %s %s %s %s %s\n\n",
		binary[0:1],
		binary[1:5], binary[5:9],
		binary[9:12], binary[12:16], binary[16:20],
		binary[20:24], binary[24:28], binary[28:32])
}
