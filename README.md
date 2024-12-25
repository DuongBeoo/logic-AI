# **Câu 1**
- Biểu thức được phân tích thành một cây, mỗi nút đại diện cho một toán tử hoặc một biến.
- Các nút lá là biến logic, các nút khác là toán tử.
- Lớp `Node` là lớp cơ sở trừu tượng.
- `VariableNode` đại diện cho một biến logic.
- `OperatorNode` đại diện cho các toán tử logic như ¬, ∧, ∨, →.
- Hàm `parseExpression`: Phân tích biểu thức từ chuỗi và xây dựng cây cú pháp.
- Hàm `evaluate`: Đệ quy tính giá trị của cây cú pháp dựa trên giá trị các biến.
# **Câu 2**
- Không sử dụng cây cú pháp : Tính giá trị biểu thức trực tiếp bằng cách duyệt qua chuỗi ký tự.
- Sử dụng ngăn xếp (`stack`) để lưu trữ toán hạng và toán tử.
- Hàm `evaluateExpression`: Phân tích biểu thức và tính giá trị theo từng toán tử.
- Đơn giản hóa logic: Trực tiếp xử lý biểu thức bằng cách duyệt từng ký tự.
