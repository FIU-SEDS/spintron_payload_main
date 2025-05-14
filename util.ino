// Function to print a vector of any type (using a template)
template <typename T>
void printVector(const std::vector<T>& vec) {
  Serial.print("[ ");

  for (size_t i = 0; i < vec.size(); ++i) {
    Serial.print(vec[i]);
    if (i < vec.size() - 1) {
      Serial.print(", ");
    }
  }
  
  Serial.println(" ]");
}