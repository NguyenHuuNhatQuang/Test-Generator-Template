# Test-Generator-Template

Template sinh test theo format Themis, phát triển bởi Câu lạc bộ TLE.

Bạn cần đọc kỹ để hiểu rõ cách hoạt động và các tính năng hỗ trợ của template.

### Cấu trúc và sơ lược cách hoạt động của template
- Template gồm một thư mục `TestGeneratorTemplate` và 5 file `RUNME.cpp`, `create.h`, `generator.h`, `solution.cpp`, `template.h`. Trong đó, `RUNME.cpp` là file bạn cần biên dịch và khởi chạy để thực hiện quá trình sinh test; `generator.h` là file dùng để viết hàm sinh test (test generator); `solution.cpp` là file dùng để chứa lời giải để sinh ra output từ input có sẵn.
- Khi file `RUNME.cpp` được biên dịch và khởi chạy, nó sẽ gọi hàm `create_all_and_compile (prob_name, testnum);` trong thư viện `template.h`, với `prob_name` và `testnum` **là hai giá trị có thể sửa đổi được ở dòng 7 và 8 của file `RUNME.cpp`**, lần lượt là mã của bài tập (mặc định là `testcase`) và số lượng test cho bài tập đó (mặc định là 100).
- Chương trình sẽ thực hiện sinh từng test theo thứ tự từ 0001 đến `testnum`.
  * Đầu tiên, chương trình sẽ gọi hàm sinh test `gen (iTest, testnum, target_file)` trong thư viện `generator.h`. **Đây là hàm bạn cần phải hoàn thành trước khi biên dịch và chạy file `RUNME.cpp`. Hàm này cần phải nhận vào ba giá trị `iTest` - thứ tự của test hiện tại, - `testnum` - số lượng test cần sinh - và `target_file` - tên file bạn cần xuất dữ liệu về input (mặc định là `input.txt`). Hàm này cần tạo ra input của test và đưa nó vào file có tên là giá trị của biến `target_file`. Để viết hàm, bạn có thể sử dụng một số hàm được viết sẵn trong thư mục `template.h` (sẽ nêu chi tiết ở mục sau)**
  * Tiếp theo, chương trình sẽ tiến hành sao chép input từ file `input.txt` sang một thư mục khác trong thư mục có tên là giá trị của biến `prob_name`.
  * Sau đó, chương trình sẽ khởi chạy file `solution.exe` (được biên dịch từ file `solution.cpp`). **File `solution.cpp` cần chứa lời giải của bài toán, với input từ file `input.txt` và xuất kết quả ra file `output.txt`.**
  * Cuối cùng, chương trình tiến hành sao chép output từ file `output.txt` sang một thư mục khác tương tự như trên.
- Sau khi quá trình sinh test kết thúc, thư mục sẽ có thêm một vài file rác (`RUNME.o`, `RUNME.exe`, `solution.exe`, `input.txt`, `output.txt`) và một thư mục mới. Đây là thư mục chứa test theo đúng format Themis của bạn.

### Các tính năng được hỗ trợ (các hàm trong `template.h`)
- `Rnd()`: trả về một số ngẫu nhiên (`long long`).
- `Rand(l, h)`: trả về một số trong đoạn `[l, h]` (`long long`).
- `bit01()`: trả về `True` hoặc `False`.
- `az()`: trả về một ký tự Latin thường.
- `AZ()`: trả về một ký tự Latin hoa.
- `num()`: trả về một ký tự số.
- `ShuffleArray(arr, n)`: hoán vị `n` phần tử đầu tiên của vector `arr`.
- `bignum(l)`: trả về một số tự nhiên lớn có `l` chữ số.
- `tree(ver, d)`: trả về danh sách cạnh của một cây có `ver` đỉnh dưới dạng `vector<pair<int, int>>`. `d` là một tham số liên quan đến độ sâu của cây, `d` càng nhỏ thì độ cao của cây càng lớn, `d = 1` thì cây sẽ là đường thẳng. Đặt `d = 0` nếu không quan tâm đến độ cao của cây, ngược lại `d` nên không quá `10`.
- `graph(ver, edge)`: trả về danh sách cạnh của một đồ thị có `ver` đỉnh và `edge` cạnh.
- `connected_graph(ver, edge)`: trả về danh sách cạnh của một đồ thị liên thông có `ver` đỉnh và `edge` cạnh.
- `log_rand(n)`: trả về một số ngẫu nhiên từ 1 đến `n`, những số nhỏ sẽ có xác suất trả về cao hơn.
- `bracket(n, d)`: trả về một dãy ngoặc đúng độ dài `2 * n`, với `d` là tham số tương tự hàm sinh cây.
