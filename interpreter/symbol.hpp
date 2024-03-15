class Type :  public AST {
 public:
    Type(const std::string &n) : name(n) {}
    void printOn(std::ostream &out) const override {
        out << "Type(" << name << ")";
    }
 private:
    std::string name;
};