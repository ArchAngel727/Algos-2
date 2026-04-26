import os
import subprocess

def main():
    for (root, dirs, files) in os.walk("./tests/"):
        if len(files) >= 2:
            expected_result = ""

            with open(f"{root}/{files[-1]}") as f:
                expected_result = f.read().strip()

            cmd = ["./main", *[f"{root}/{file}" for file in files[:-1]]]
            print(f"cmd: {" ".join(cmd)}")
            result = subprocess.run(cmd, capture_output=True)
            res = "".join([chr(byte) for byte in result.stdout])

            print("---")
            print(res)
            print("---")

            if (res == expected_result):
                print("Test passed\n")
            else:
                print("Test failed\n")

if __name__ == "__main__":
    main()
