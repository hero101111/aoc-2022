#pragma once

using LL  = long long;
using ULL = unsigned long long;

template <typename T>
bool _assert_aoc_helper(T value, T expectedValue, string descr = "")
{
  if (expectedValue != value)
  {
    cout << "ASSERT_FAIL " << descr << " should be " << expectedValue << ", got " << value << endl;
    return false;
  }
  return true;
}

#define aoc_assert(value, expectedValue)                     \
  {                                                          \
    if (!_assert_aoc_helper(value, expectedValue, ""s))      \
      cout << "  " << __FILE__ << " : " << __LINE__ << endl; \
  }

void pic(string data)
{
#ifdef _MSC_VER
  const char * output = data.c_str();
  const size_t len    = strlen(output) + 1;
  HGLOBAL      hMem   = GlobalAlloc(GMEM_MOVEABLE, len);
  memcpy(GlobalLock(hMem), output, len);
  GlobalUnlock(hMem);
  OpenClipboard(nullptr);
  EmptyClipboard();
  SetClipboardData(CF_TEXT, hMem);
  CloseClipboard();
#endif
#ifdef __APPLE__
  const char proto_cmd[] = "echo '%s' | pbcopy";
  char cmd[strlen(data.c_str()) + strlen(proto_cmd) - 1];  // -2 to remove the length of %s in proto
                                                           // cmd and + 1 for null terminator = -1
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
  sprintf(cmd, proto_cmd, data.c_str());
#pragma clang diagnostic pop
  system(cmd);
#endif
}

template <class T>
void pic(T v)
{
  return pic(std::to_string(v));
}

template <typename T>
auto vec2set(vector<T> v) -> set<T>
{
  set<T> ret;
  for (auto d : v)
  {
    ret.insert(d);
  }
  return ret;
}

template <typename T>
auto setContains(const set<T> & big, const set<T> & smallSet) -> bool
{
  for (auto el : smallSet)
  {
    if (big.find(el) == end(big))
    {
      return false;
    }
  }
  return true;
}

template <typename T>
auto setContains(const set<T> & big, const T & val) -> bool
{
  return big.find(val) != end(big);
}

template <typename T>
auto getDifference(T a, T b) -> T
{
  T ret;
  for (auto el : a)
  {
    if (b.find(el) == end(b))
    {
      ret.insert(el);
    }
  }
  return ret;
}

template <typename T>
auto getSetEqCount(const unordered_set<T> & a, const unordered_set<T> & b) -> LL
{
  LL ret = 0;
  for (auto el : a)
  {
    if (b.find(el) != end(b))
    {
      ret++;
    }
  }
  return ret;
}

auto tok(string str, char sep = ' ') -> vector<string>
{
  stringstream s(str);  // Used for breaking words
  string       word;    // to store individual words

  vector<string> ret;

  while (getline(s, word, sep))
  {
    ret.push_back(word);
  }

  return ret;
}

template <typename T>
T getsign(T val)
{
  if (val == 0)
    return 0;
  return val > 0 ? 1 : -1;
}

auto split(string str, char sep = ' ') -> pair<string, string>
{
  auto tokens = tok(str, sep);
  assert(tokens.size() == 2);
  return make_pair(tokens[0], tokens[1]);
}

auto getStream(string filePath, bool append) -> ofstream
{
  ofstream fOut;
  fOut.open(filePath, append ? ios_base::app : ios_base::out);
  return fOut;
}

void fprintf(string filePath, string message, bool append = false)
{
  ofstream fOut;
  fOut.open(filePath, append ? ios_base::app : ios_base::out);

  if (append)
  {
    fOut << endl;
  }
  if (!message.empty())
  {
    fOut << message;
  }
}

template <class T>
auto join(const list<T> & v, string sep = ","s) -> string
{
  string ret;
  for (auto i = begin(v); i != end(v); ++i)
  {
    ret += to_string(*i);
    if (distance(i, end(v)) >= 2)
      ret += sep;
  }
  return ret;
}

template <class T>
auto join(const vector<T> & v, string sep = ","s) -> string
{
  string ret;
  for (auto i = begin(v); i != end(v); ++i)
  {
    ret += to_string(*i);
    if (distance(i, end(v)) >= 2)
      ret += sep;
  }
  return ret;
}

template <>
auto join(const vector<string> & v, string sep) -> string
{
  string ret;
  for (auto i = begin(v); i != end(v); ++i)
  {
    ret += *i;
    if (distance(i, end(v)) >= 2)
    {
      ret += sep;
    }
  }
  return ret;
}

auto stoll(const vector<string> & aVec) -> vector<LL>
{
  vector<LL> ret;
  for (auto d : aVec)
  {
    if (d.empty())
    {
      continue;
    }
    ret.push_back(stoll(d));
  }
  return ret;
}

auto sinDegress(int angle) -> double
{
  if (angle == 0)
  {
    return 0;
  }
  if (angle == 90)
  {
    return 1;
  }
  if (angle == 180)
  {
    return 0;
  }
  if (angle == 270)
  {
    return -1;
  }

  double toRad = angle * 3.14159265358979 / 180.0;
  return sin(toRad);
}

auto cosDegrees(int angle) -> double
{
  if (angle == 0)
  {
    return 1;
  }
  if (angle == 90)
  {
    return 0;
  }
  if (angle == 180)
  {
    return -1;
  }
  if (angle == 270)
  {
    return 0;
  }

  double toRad = angle * 3.14159265358979 / 180.0;
  return cos(toRad);
}

struct Point
{
  long long x{ 0 }, y{ 0 }, z{ 0 }, w{ 0 };

  Point() = default;
  Point(long long ax, long long ay = 0, long long az = 0, long long aw = 0)
    : x(ax)
    , y(ay)
    , z(az)
    , w(aw)
  {
  }
  Point(string ax, string ay = "0", string az = "0", string aw = "0")
    : x(stoll(ax))
    , y(stoll(ay))
    , z(stoll(az))
    , w(stoll(aw))
  {
  }
  Point(tuple<string, string> coord)
    : x(stoll(get<0>(coord)))
    , y(stoll(get<1>(coord)))
  {
  }
  Point(tuple<string, string, string> coord)
    : x(stoll(get<0>(coord)))
    , y(stoll(get<1>(coord)))
    , z(stoll(get<2>(coord)))
  {
  }

  auto operator[](int index) -> long long &
  {
    if (index == 0)
    {
      return x;
    }
    if (index == 1)
    {
      return y;
    }
    if (index == 2)
    {
      return z;
    }
    if (index == 3)
    {
      return w;
    }
    assert(!"Invalid coordinate");
    return x;
  }

  auto operator[](int index) const -> const long long &
  {
    if (index == 0)
    {
      return x;
    }
    if (index == 1)
    {
      return y;
    }
    if (index == 2)
    {
      return z;
    }
    if (index == 3)
    {
      return w;
    }
    assert(!"Invalid coordinate");
    return x;
  }
  auto operator[](string index) const -> const long long &
  {
    if (index == "x" || index == "X")
    {
      return x;
    }
    if (index == "y" || index == "Y")
    {
      return y;
    }
    if (index == "z" || index == "Z")
    {
      return z;
    }
    if (index == "w" || index == "W")
    {
      return w;
    }
    assert(!"Invalid coordinate");
    return x;
  }

  auto operator==(const Point & other) const -> bool
  {
    return x == other.x && y == other.y && z == other.z && w == other.w;
  }

  auto operator!=(const Point & other) const -> bool { return !operator==(other); }

  auto operator-(const Point & other) const -> Point
  {
    return { x - other.x, y - other.y, z - other.z, w - other.w };
  }

  auto operator+(const Point & other) const -> Point
  {
    return { x + other.x, y + other.y, z + other.z, w + other.w };
  }

  auto operator*(LL factor) const -> Point { return { x * factor, y * factor, z * factor }; }

  auto operator<(const Point & other) const -> bool
  {
    if (other.y < y)
    {
      return true;
    }
    if (y == other.y && x < other.x)
    {
      return true;
    }
    if (y == other.y && x == other.x && z < other.z)
    {
      return true;
    }
    if (y == other.y && x == other.x && z == other.z && w < other.w)
    {
      return true;
    }
    return false;
  }

  [[nodiscard]] auto Down() const -> Point { return Point{ x, y + 1, z, w }; }

  [[nodiscard]] auto Up() const -> Point { return Point{ x, y - 1, z, w }; }

  [[nodiscard]] auto Left() const -> Point { return Point{ x - 1, y, z, w }; }

  [[nodiscard]] auto Right() const -> Point { return Point{ x + 1, y, z, w }; }

  [[nodiscard]] auto UpLeft() const -> Point { return Point{ x - 1, y - 1, z, w }; }

  [[nodiscard]] auto UpRight() const -> Point { return Point{ x + 1, y - 1, z, w }; }

  [[nodiscard]] auto DownLeft() const -> Point { return Point{ x - 1, y + 1, z, w }; }

  [[nodiscard]] auto DownRight() const -> Point { return Point{ x + 1, y + 1, z, w }; }

  enum class Axis
  {
    X = 0,
    Y,
    Z
  };

  auto GetRotatedAround(Point pivot, int rotAngleDegrees, Axis axis) -> Point
  {
    Point toRotate = *this - pivot;
    // int sign = -1;

    /*if (rotAngleDegrees < 0)
    {
      sign = 1;
      rotAngleDegrees *= -1;
    }*/

    Point ret;
    if (axis == Axis::X)
    {
      ret.x = (LL)(toRotate.x);
      ret.y =
        (LL)(toRotate.y * cosDegrees(rotAngleDegrees) - toRotate.z * sinDegress(rotAngleDegrees));
      ret.z =
        (LL)(toRotate.y * sinDegress(rotAngleDegrees) + toRotate.z * cosDegrees(rotAngleDegrees));
    }
    if (axis == Axis::Y)
    {
      ret.x =
        (LL)(toRotate.x * cosDegrees(rotAngleDegrees) + toRotate.z * sinDegress(rotAngleDegrees));
      ret.y = (LL)(toRotate.y);
      ret.z =
        (LL)(-sinDegress(rotAngleDegrees) * toRotate.x + toRotate.z * cosDegrees(rotAngleDegrees));
    }
    if (axis == Axis::Z)
    {
      ret.x =
        (LL)(toRotate.x * cosDegrees(rotAngleDegrees) - toRotate.y * sinDegress(rotAngleDegrees));
      ret.y =
        (LL)(toRotate.x * sinDegress(rotAngleDegrees) + toRotate.y * cosDegrees(rotAngleDegrees));
      ret.z = (LL)(toRotate.z);
    }

    ret = ret + pivot;

    return ret;
  }

  static auto Parse(string stringValue) -> Point
  {
    Point ret;
    if (stringValue.empty())
    {
      return ret;
    }

    if (stringValue[0] == '(')
    {
      stringValue.erase(begin(stringValue));
    }
    if (stringValue.back() == ')')
    {
      stringValue.erase(end(stringValue) - 1);
    }

    auto tokens = tok(stringValue, ',');
    assert(tokens.size() >= 2);
    ret.x = stoll(tokens[0]);
    ret.y = stoll(tokens[1]);
    if (tokens.size() > 2)
    {
      ret.z = stoll(tokens[2]);
    }
    if (tokens.size() > 3)
    {
      ret.w = stoll(tokens[3]);
    }

    return ret;
  }

  [[nodiscard]] auto ToString() const -> string
  {
    string s = "(";
    s += to_string(x);
    s += ", ";
    s += to_string(y);
    s += ")";
    return s;
  }

  [[nodiscard]] auto ToString3() const -> string
  {
    string s = "(";
    s += to_string(x);
    s += ", ";
    s += to_string(y);
    s += ", ";
    s += to_string(z);
    s += ")";
    return s;
  }

  [[nodiscard]] auto FromOrientation(char orientation) const -> Point
  {
    switch (orientation)
    {
    case 'N':
    case 'n':
      return Up();
    case 'e':
    case 'E':
      return Right();
    case 'w':
    case 'W':
      return Left();
    case 's':
    case 'S':
      return Down();
    }
    return *this;
  }

  [[nodiscard]] auto Slope(const Point & other) const -> float
  {
    if (other.x == this->x)
    {
      return numeric_limits<float>::max();
    }

    return ((float)other.y - this->y) / ((float)other.x - this->x);
  }

  [[nodiscard]] auto crossProduct(const Point & other) const -> Point
  {
    return { y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x };
  }

  [[nodiscard]] auto Angle(const Point & other) const -> double
  {
    double angle        = atan2(this->y - (double)other.y, this->x - (double)other.x);
    double angleDegrees = 180.0 / 3.14159265359 * angle;

    angleDegrees -= 90;
    if (angleDegrees < -0.00001)
    {
      angleDegrees = 360 + angleDegrees;
    }
    return angleDegrees;
  }

  // Get the quadrant in which another point is relative to this one
  // Y goes down, as in computer screen, inversely to math
  auto GetQuadrant(Point target) -> int
  {
    const bool targetGoesRight = target.x > x;
    const bool targetGoesDown  = target.y > y;

    if (targetGoesRight && !targetGoesDown)
    {
      return 1;
    }
    if (!targetGoesRight && !targetGoesDown)
    {
      return 2;
    }
    if (!targetGoesRight && targetGoesDown)
    {
      return 3;
    }
    else if (targetGoesRight && targetGoesDown)
    {
      return 4;
    }
    assert(!"invalid");
    return -1;
  }

  static auto ArrowToDirection(char arrow) -> char
  {
    switch (arrow)
    {
    case '<':
      return 'l';
    case '>':
      return 'r';
    case 'v':
      return 'd';
    case '^':
      return 'u';
    }
    assert("!Invalid");
    return 'x';
  }

  static auto DirectionToArrow(char dir) -> char
  {
    switch (dir)
    {
    case 'd':
    case 'v':
      return 'v';
    case 'u':
      return '^';
    case 'l':
      return '<';
    case 'r':
      return '>';
    }
    assert(!"Invalid");
    return 'x';
  }

  [[nodiscard]] auto FromDirection(char orientation) const -> Point
  {
    switch (orientation)
    {
    case 'u':
    case 'U':
    case '^':
      return Up();
    case 'r':
    case 'R':
    case '>':
      return Right();
    case 'l':
    case 'L':
    case '<':
      return Left();
    case 'd':
    case 'D':
    case 'v':
      return Down();
    }
    return *this;
  }

  static auto RotateDirection(char c, bool left) -> char
  {
    if (left)
    {
      switch (c)
      {
      case '^':
      case 'u':
        return 'l';
        break;
      case '<':
      case 'l':
        return 'd';
        break;
      case 'v':
      case 'd':
        return 'r';
        break;
      case '>':
      case 'r':
        return 'u';
        break;
      default:
        assert(!"Unsupported");
      }
    }
    else
    {
      switch (c)
      {
      case '^':
      case 'u':
        return 'r';
        break;
      case '<':
      case 'l':
        return 'u';
        break;
      case 'v':
      case 'd':
        return 'l';
        break;
      case '>':
      case 'r':
        return 'd';
        break;
      default:
        assert(!"Unsupported");
      }
    }
  }

  [[nodiscard]] auto GetNeighbours() const -> vector<Point>
  {
    vector<Point> ret;
    ret.push_back(Left());
    ret.push_back(Up());
    ret.push_back(Right());
    ret.push_back(Down());

    ret.push_back(Up().Left());
    ret.push_back(Up().Right());
    ret.push_back(Down().Left());
    ret.push_back(Down().Right());

    return ret;
  }

  [[nodiscard]] auto GetNeighbours(int level) -> vector<Point>
  {
    auto          me = *this;
    vector<Point> ret;
    while (level >= 1)
    {
      vector<Point> corners = { Point{ -level, -level }, Point{ level, -level },
                                Point{ level, level }, Point{ -level, level } };
      for (auto & c : corners)
        c = c + me;

      for (auto e1 = corners[0].GetTo(corners[1]); auto e : e1)
        ret.push_back(e);
      for (auto e1 = corners[1].GetTo(corners[2]); auto e : e1)
        ret.push_back(e);
      for (auto e1 = corners[2].GetTo(corners[3]); auto e : e1)
        ret.push_back(e);
      for (auto e1 = corners[3].GetTo(corners[0]); auto e : e1)
        ret.push_back(e);

      level -= 1;
    }
    return ret;
  }

  [[nodiscard]] auto GetDirectNeighbours() const -> vector<Point>
  {
    vector<Point> ret;
    ret.push_back(Left());
    ret.push_back(Up());
    ret.push_back(Right());
    ret.push_back(Down());

    return ret;
  }

  [[nodiscard]] auto ManhattanDist(const Point & p) const -> long long
  {
    return abs(x - p.x) + abs(y - p.y) + abs(z - p.z) + abs(w - p.w);
  }

  auto ChebyshevDist(const Point & p) const -> long long
  {
    auto onx  = abs(x - p.x);
    auto ony  = abs(y - p.y);
    auto onz  = abs(z - p.z);
    auto onw  = abs(w - p.w);
    auto dist = max(onx, ony);
    dist      = max(dist, onz);
    dist      = max(dist, onw);
    return dist;
  }

  [[nodiscard]] auto DistanceTo(const Point & p) const -> double
  {
    return sqrt(pow(p.x - x, 2) + pow(p.y - y, 2) + pow(p.z - z, 2) + pow(p.w - w, 2));
  }

  [[nodiscard]] auto IsInGrid(int width, int height, int depth = 0) const -> bool
  {
    return x >= 0 && y >= 0 && x < width && y < height && z >= 0 && z < depth;
  }

  [[nodiscard]] auto GetTo(Point b, bool walkInStraightLines = false) const -> vector<Point>
  {
    auto x1 = this->x;
    auto y1 = this->y;
    auto x2 = b.x;
    auto y2 = b.y;

    vector<Point> ret;
    if (y1 == y2)
    {
      for (auto x = min(x1, x2); x <= max(x1, x2); ++x)
      {
        ret.emplace_back(x, y1);
      }
      if (x2 < x1)
        reverse(begin(ret), end(ret));
    }
    else if (x1 == x2)
    {
      for (auto y = min(y1, y2); y <= max(y1, y2); ++y)
      {
        ret.emplace_back(x1, y);
      }
      if (y2 < y1)
        reverse(begin(ret), end(ret));
    }
    else if (!walkInStraightLines && x1 > x2 && y1 > y2)
    {
      for (auto x = x2, y = y2; y <= y1; ++y, ++x)
      {
        ret.emplace_back(x, y);
      }
    }
    else if (!walkInStraightLines && x1 < x2 && y1 > y2)
    {
      for (auto x = x1, y = y1; x <= x2; --y, ++x)
      {
        ret.emplace_back(x, y);
      }
    }
    else if (!walkInStraightLines && x1 < x2 && y1 < y2)
    {
      for (auto x = x1, y = y1; y <= y2; ++y, ++x)
      {
        ret.emplace_back(x, y);
      }
    }
    else if (!walkInStraightLines && x1 > x2 && y1 < y2)
    {
      for (auto x = x2, y = y2; x <= x1; --y, ++x)
      {
        ret.emplace_back(x, y);
      }
    }
    return ret;
  }
};

enum class WalkDirection
{
  Up = 0,
  Right,
  Down,
  Left
};

static const WalkDirection WalkDirections[4] = { WalkDirection::Right, WalkDirection::Left,
                                                 WalkDirection::Down, WalkDirection::Up };

auto operator<<(ostream & out, const Point & c) -> ostream &
{
  out << c.ToString3() << "\t\t";
  return out;
}

auto RegexMatch(string s, string regex) -> vector<string>
{
  std::regex  re2(regex);
  std::smatch match2;
  std::regex_search(s, match2, re2);
  vector<string> ret;
  for (size_t i = 1; i < match2.size(); ++i)
  {
    ret.push_back(match2.str(i));
  }
  return ret;
}

tuple<LL> tuple_toll(tuple<string> t)
{
  return make_tuple(stoll(get<0>(t)));
}

tuple<LL, LL> tuple_toll(tuple<string, string> t)
{
  return make_tuple(stoll(get<0>(t)), stoll(get<1>(t)));
}

tuple<LL, LL, LL> tuple_toll(tuple<string, string, string> t)
{
  return make_tuple(stoll(get<0>(t)), stoll(get<1>(t)), stoll(get<2>(t)));
}

tuple<LL, LL, LL, LL> tuple_toll(tuple<string, string, string, string> t)
{
  return make_tuple(stoll(get<0>(t)), stoll(get<1>(t)), stoll(get<2>(t)), stoll(get<3>(t)));
}

tuple<LL, LL, LL, LL, LL> tuple_toll(tuple<string, string, string, string, string> t)
{
  return make_tuple(stoll(get<0>(t)), stoll(get<1>(t)), stoll(get<2>(t)), stoll(get<3>(t)),
                    stoll(get<4>(t)));
}

tuple<LL, LL, LL, LL, LL, LL> tuple_toll(tuple<string, string, string, string, string, string> t)
{
  return make_tuple(stoll(get<0>(t)), stoll(get<1>(t)), stoll(get<2>(t)), stoll(get<3>(t)),
                    stoll(get<4>(t)), stoll(get<5>(t)));
}

auto RegExMatchN(string s, string regexExp) -> vector<string>
{
  vector<string> ret;
  regex          regexObj(regexExp);
  for (sregex_iterator it = sregex_iterator(s.begin(), s.end(), regexObj); it != sregex_iterator();
       ++it)
  {
    smatch match = *it;
    ret.push_back(match.str());
  }
  return ret;
}

auto RegExMatch1(string s, string regex) -> tuple<string>
{
  auto          data = RegexMatch(s, regex);
  tuple<string> ret;
  get<0>(ret) = data[0];
  return ret;
}

auto RegExMatch2(string s, string regex) -> tuple<string, string>
{
  auto                  data = RegexMatch(s, regex);
  tuple<string, string> ret;
  get<0>(ret) = data[0];
  get<1>(ret) = data[1];
  return ret;
}

auto RegExMatch3(string s, string regex) -> tuple<string, string, string>
{
  auto                          data = RegexMatch(s, regex);
  tuple<string, string, string> ret;
  get<0>(ret) = data[0];
  get<1>(ret) = data[1];
  get<2>(ret) = data[2];
  return ret;
}

auto RegExMatch4(string s, string regex) -> tuple<string, string, string, string>
{
  auto                                  data = RegexMatch(s, regex);
  tuple<string, string, string, string> ret;
  get<0>(ret) = data[0];
  get<1>(ret) = data[1];
  get<2>(ret) = data[2];
  get<3>(ret) = data[3];
  return ret;
}

auto RegExMatch5(string s, string regex) -> tuple<string, string, string, string, string>
{
  auto                                          data = RegexMatch(s, regex);
  tuple<string, string, string, string, string> ret;
  get<0>(ret) = data[0];
  get<1>(ret) = data[1];
  get<2>(ret) = data[2];
  get<3>(ret) = data[3];
  get<4>(ret) = data[4];
  return ret;
}

auto RegExMatch6(string s, string regex) -> tuple<string, string, string, string, string, string>
{
  auto                                                  data = RegexMatch(s, regex);
  tuple<string, string, string, string, string, string> ret;
  get<0>(ret) = data[0];
  get<1>(ret) = data[1];
  get<2>(ret) = data[2];
  get<3>(ret) = data[3];
  get<4>(ret) = data[4];
  get<5>(ret) = data[5];
  return ret;
}

auto RegExMatch7(string s, string regex)
  -> tuple<string, string, string, string, string, string, string>
{
  auto                                                          data = RegexMatch(s, regex);
  tuple<string, string, string, string, string, string, string> ret;
  get<0>(ret) = data[0];
  get<1>(ret) = data[1];
  get<2>(ret) = data[2];
  get<3>(ret) = data[3];
  get<4>(ret) = data[4];
  get<5>(ret) = data[5];
  get<6>(ret) = data[6];
  return ret;
}

auto RegExIsMatch(string s, string regex) -> bool
{
  std::regex  re2(regex);
  std::smatch match2;
  return std::regex_search(s, match2, re2);
}

auto RegExReplace(string s, string rgx, string replace) -> string
{
  regex re(rgx);
  return regex_replace(s, re, replace);
}

auto RegExReplace(string s, initializer_list<pair<string, string>> replace) -> string
{
  for (auto kv : replace)
  {
    s = RegExReplace(s, kv.first, kv.second);
  }
  return s;
}

template <class T>
auto GetDigits(T n) -> vector<T>
{
  if (n == 0)
    return { 0 };

  vector<T> ret;
  while (n > 0)
  {
    ret.insert(begin(ret), n % 10);
    n /= 10;
  }
  return ret;
}

auto rff(string filePath, function<void(string &)> func = nullptr) -> vector<string>
{
  vector<string> ret;
  ifstream       f;
  f.open(filePath);
  string s;

  while (getline(f, s))
  {
    if (func != nullptr)
    {
      func(s);
    }
    ret.push_back(s);
  }

  return ret;
}

auto rffv(string filePath, function<void(string &)> func = nullptr) -> vector<vector<string>>
{
  vector<vector<string>> ret;
  ifstream               f;
  f.open(filePath);
  string s;

  vector<string> v;
  while (getline(f, s))
  {
    if (func != nullptr)
    {
      func(s);
    }

    if (!s.empty())
      v.push_back(s);
    else
    {
      ret.push_back(v);
      v.clear();
    }
  }
  if (v.size() > 0)
    ret.push_back(v);

  return ret;
}

auto rffll(string filePath, function<void(string &)> func = nullptr) -> vector<LL>
{
  vector<LL> ret;
  ifstream   f;
  f.open(filePath);
  string s;

  while (getline(f, s))
  {
    if (func != nullptr)
    {
      func(s);
    }
    ret.push_back(stoll(s));
  }

  return ret;
}

auto ltrim(string str) -> string
{
  while (!str.empty() && str.front() == ' ')
  {
    str.erase(begin(str));
  }
  return str;
}

auto rtrim(string str) -> string
{
  while (!str.empty() && str.back() == ' ')
  {
    str.pop_back();
  }
  return str;
}

auto trim(string str) -> string
{
  return ltrim(rtrim(str));
}

auto manhattan(LL x1, LL y1, LL x2, LL y2) -> LL
{
  return abs(x1 - x2) + abs(y1 - y2);
}

auto tolower_str(string s) -> string
{
  string newS = s;
  transform(begin(newS), end(newS), begin(newS), ::tolower);
  return newS;
}

auto replacestr(string str, const string & search, string replace) -> string
{
  size_t pos = 0;
  while ((pos = str.find(search, pos)) != std::string::npos)
  {
    str.replace(pos, search.length(), replace);
    pos += replace.length();
  }
  return str;
}

auto getcharfreq(string str) -> unordered_map<char, int>
{
  unordered_map<char, int> ret;
  for (char c : str)
    ret[c] += 1;
  return ret;
}

template <class T>
class DynamicMap
{
public:
  using DT = unordered_map<long long, unordered_map<long long, T>>;

  DT data;

  long long max_y = numeric_limits<int>::min();
  long long max_x = numeric_limits<int>::min();
  long long min_x = numeric_limits<int>::max();
  long long min_y = numeric_limits<int>::max();

  auto operator=(const DynamicMap<T> & other) -> DynamicMap<T> &
  {
    max_y = other.max_y;
    max_x = other.max_x;
    min_x = other.min_x;
    min_y = other.min_y;

    data = other.data;

    return *this;
  }

  auto operator=(const vector<T> & aOther) -> DynamicMap<T> &
  {
    max_y = numeric_limits<LL>::min();
    max_x = numeric_limits<LL>::min();
    min_x = numeric_limits<LL>::max();
    min_y = numeric_limits<LL>::max();
    data  = {};
    for (size_t i = 0; i < aOther.size(); ++i)
    {
      set(i, aOther[i]);
    }
    return *this;
  }

  auto at(Point p, T * aOutVal) -> bool
  {
    auto xData = data.find(p.x);
    if (xData == end(data))
    {
      return false;
    }
    auto yData = xData->second.find(p.y);
    if (yData == end(xData->second))
    {
      return false;
    }

    if (aOutVal != nullptr)
    {
      *aOutVal = yData->second;
    }

    return true;
  }

  auto isSetAt(Point p) -> bool
  {
    T c;
    return at(p, &c);
  }

  auto at(Point p, T * const aOutVal) const -> bool
  {
    auto xData = data.find(p.x);
    if (xData == end(data))
    {
      return false;
    }
    auto yData = xData->second.find(p.y);
    if (yData == end(xData->second))
    {
      return false;
    }

    if (aOutVal != nullptr)
    {
      *aOutVal = yData->second;
    }

    return true;
  }

  auto hasAt(Point p, const T & aVal) -> bool
  {
    auto xData = data.find(p.x);
    if (xData == end(data))
      return false;
    auto yData = xData->second.find(p.y);
    if (yData == end(xData->second))
      return false;

    return aVal == yData->second;
  }

  void set(Point p, T value)
  {
    if (p.x < min_x)
    {
      min_x = p.x;
    }
    if (p.x > max_x)
    {
      max_x = p.x;
    }
    if (p.y < min_y)
    {
      min_y = p.y;
    }
    if (p.y > max_y)
    {
      max_y = p.y;
    }

    data[p.x][p.y] = value;
  }

  auto operator[](Point p) -> T &
  {
    if (!at(p, nullptr))
    {
      set(p, T());
    }
    return data[p.x][p.y];
  }

  [[nodiscard]] auto GetLine(LL y) const -> vector<T>
  {
    vector<T> ret;
    LL        startX = min_x;
    T         content;
    for (; startX <= max_x; ++startX)
    {
      if (at({ startX, y }, &content))
      {
        ret.push_back(content);
      }
    }
    return ret;
  }

  [[nodiscard]] auto GetColumn(LL x) const -> vector<T>
  {
    vector<T> ret;
    LL        startY = min_y;
    T         content;
    for (; startY <= max_y; ++startY)
    {
      if (at({ x, startY }, &content))
      {
        ret.push_back(content);
      }
    }
    return ret;
  }

  auto walkToBorder(Point p, WalkDirection dir, function<bool(Point p)> aPred = nullptr)
    -> vector<Point>
  {
    vector<Point> walk;
    if (dir == WalkDirection::Up)
      walk = p.GetTo({ p.x, this->min_y }, true);
    else if (dir == WalkDirection::Down)
      walk = p.GetTo({ p.x, this->max_y }, true);
    else if (dir == WalkDirection::Left)
      walk = p.GetTo({ this->min_x, p.y }, true);
    else if (dir == WalkDirection::Right)
      walk = p.GetTo({ this->max_x, p.y }, true);

    return walk;
  }

  auto operator==(const DynamicMap<T> & other) const -> bool
  {
    if (min_x != other.min_x)
      return false;
    if (min_y != other.min_y)
      return false;
    if (max_x != other.max_x)
      return false;
    if (max_y != other.max_y)
      return false;

    for (long long x : range_x())
    {
      for (long long y : range_y())
      {
        Point p{ x, y };
        T     myV, theirV;

        bool IHave    = at(p, &myV);
        bool theyHave = other.at(p, &theirV);

        if (IHave != theyHave)
          return false;

        if (myV != theirV)
          return false;
      }
    }
    return true;
  }

  [[nodiscard]] auto range_x() const -> vector<LL>
  {
    vector<LL> ret(width());
    iota(begin(ret), end(ret), min_x);
    return ret;
  }

  [[nodiscard]] auto range_y() const -> vector<LL>
  {
    vector<LL> ret(height());
    iota(begin(ret), end(ret), min_y);
    return ret;
  }

  [[nodiscard]] auto empty() const -> bool { return data.empty(); }

  [[nodiscard]] auto width() const -> long long { return abs(max_x - min_x) + 1; }

  [[nodiscard]] auto height() const -> long long { return abs(max_y - min_y) + 1; }

  void clear() { *this = DynamicMap<T>(); }

  auto for_each(function<bool(T)> func) -> size_t
  {
    size_t ret = 0;
    for (auto i : range_x())
    {
      for (auto j : range_y())
      {
        T data;
        if (at({ i, j }, &data))
        {
          ret += func(data);
        }
      }
    }
    return ret;
  }

  auto for_each(function<bool(Point, T)> func) -> size_t
  {
    size_t ret = 0;
    for (auto i : range_x())
    {
      for (auto j : range_y())
      {
        T data;
        if (at({ i, j }, &data))
        {
          ret += func({ i, j }, data);
        }
      }
    }
    return ret;
  }

  auto for_eachYX(function<bool(Point, T)> func) -> size_t
  {
    size_t ret = 0;
    for (auto j : range_y())
    {
      for (auto i : range_x())
      {
        T data;
        if (at({ i, j }, &data))
        {
          ret += func({ i, j }, data);
        }
      }
    }
    return ret;
  }

  void transform(function<T(Point, T)> func)
  {
    for_each(
      [&](Point p, T v)
      {
        this->operator[](p) = func(p, v);
        return true;
      });
  }

  void insertAt(const DynamicMap<T> & aOther, Point originToInsertAt)
  {
    for (auto x : aOther.range_x())
    {
      for (auto y : aOther.range_y())
      {
        Point p{ x, y };
        T     v;

        if (aOther.at(p, &v))
        {
          operator[](p + originToInsertAt) = v;
        }
      }
    }
  }

  auto count() -> size_t
  {
    return for_each(
      [](T &)
      {
        return true;
      });
  }

  auto count_occurence(T val) -> size_t
  {
    return for_each(
      [val](T v)
      {
        return val == v;
      });
  }

  auto Traverse() -> vector<pair<Point, T>>
  {
    vector<pair<Point, T>> ret;
    for (int line : range_y())
      for (int col : range_x())
      {
        Point p{ col, line };
        assert(at(p, nullptr));
        ret.push_back(make_pair(p, (*this)[p]));
      }
    return ret;
  }

  void fromlines(vector<string> lines, function<T(char)> readFunc = nullptr)
  {
    if (!empty())
      clear();

    int crtLine = 0;
    for (auto & line : lines)
    {
      int crtChar = 0;
      for (char c : line)
      {
        (*this)[{ crtChar++, crtLine }] = readFunc ? readFunc(c) : c;
      }

      ++crtLine;
    }
  }

  void addlinetokenized(string line, char tokenDelimiter, function<T(string)> readFunc = nullptr)
  {
    int crtLine = max_y == numeric_limits<int>::min() ? 0 : max_y + 1;

    vector<string> tokens  = tok(line, tokenDelimiter);
    int            crtChar = 0;
    for (auto tok : tokens)
    {
      if (!tok.empty())
        (*this)[{ crtChar++, crtLine }] = readFunc ? readFunc(tok) : tok;
    }
  }

  void fromlinestokenized(vector<string>      lines,
                          char                tokenDelimiter,
                          function<T(string)> readFunc = nullptr)
  {
    for (auto & line : lines)
    {
      addlinetokenized(line, tokenDelimiter, readFunc);
    }
  }

  void fromfile(string filepath, function<T(char)> readFunc = nullptr)
  {
    vector<string> lines = rff(filepath);
    fromlines(lines, readFunc);
  }

  void fromfiletokenized(string              filepath,
                         char                tokenDelimiter,
                         function<T(string)> readFunc = nullptr)
  {
    vector<string> lines = rff(filepath);
    fromlinestokenized(lines, tokenDelimiter, readFunc);
  }

  void addline(string line, function<T(char)> readFunc = nullptr)
  {
    int crtLine = max_y == numeric_limits<int>::min() ? 0 : max_y + 1;
    int crtChar = 0;
    for (char c : line)
    {
      (*this)[{ crtChar++, crtLine }] = readFunc ? readFunc(c) : c;
    }
  }

  auto flipX() -> DynamicMap<T>
  {
    DynamicMap<T> ret = *this;
    for (auto [pos, c] : Traverse())
    {
      ret[{ ret.max_x - pos.x, pos.y }] = c;
    }
    return ret;
  }

  auto flipY() -> DynamicMap<T>
  {
    DynamicMap<T> ret = *this;
    for (auto [pos, c] : Traverse())
    {
      ret[{ pos.x, ret.max_y - pos.y }] = c;
    }
    return ret;
  }

  auto rotateClockwise() -> DynamicMap<T>
  {
    DynamicMap<T> ret = *this;
    assert(max_x == max_y && min_y == min_x);
    LL dimension = max_x + 1;

    for (LL x = min_x; x < dimension / 2; x++)
    {
      for (LL y = x; y < dimension - x - 1; y++)
      {
        LL aux        = ret[{ x, y }];
        ret[{ x, y }] = ret[{ y, dimension - 1 - x }];

        ret[{ y, dimension - 1 - x }] = ret[{ dimension - 1 - x, dimension - 1 - y }];

        ret[{ dimension - 1 - x, dimension - 1 - y }] = ret[{ dimension - 1 - y, x }];

        ret[{ dimension - 1 - y, x }] = aux;
      }
    }
    return ret;
  }

  void printf(
    std::ostream & st, char sep = ' ', char notSet = ' ', bool append = false, string prologue = "")
  {
    if (append)
    {
      st << endl;
    }
    if (!prologue.empty())
    {
      st << prologue << endl;
    }

    for (auto j : range_y())
    {
      for (auto i : range_x())
      {
        T data;
        if (!at({ i, j }, &data))
        {
          data = notSet;
        }

        st << data << sep;
      }
      st << endl;
    }
  }

  void printf(
    string filePath, char sep = ' ', char notSet = ' ', bool append = false, string prologue = "")
  {
    ofstream fOut;
    fOut.open(filePath, append ? ios_base::app : ios_base::out);
    printf(fOut, sep, notSet, append, prologue);
    fOut.close();
  }

  void printf(char sep = ' ', char notSet = ' ', bool append = false, string prologue = "")
  {
    printf(cout, sep, notSet, append, prologue);
  }
};

template <class T>
struct objmap
{
  int                   crtIndex{ 0 };
  unordered_map<T, int> mapping;

  auto add(const T & obj) -> int
  {
    auto found = mapping.find(obj);
    if (found != mapping.end())
    {
      return found->second;
    }

    mapping[obj] = crtIndex;
    return crtIndex++;
  }

  auto operator()(const T & obj) -> int { return add(obj); }

  auto operator[](const T & obj) -> int { return add(obj); }

  auto translate(int index) -> T
  {
    for (auto m : mapping)
    {
      if (m.second == index)
      {
        return m.first;
      }
    }
    return T();
  }

  auto translate(const vector<int> & path) -> vector<T>
  {
    vector<T> ret;
    for (auto p : path)
    {
      ret.push_back(translate(p));
    }
    return ret;
  }
};

//--------------------------------------

template <>
struct hash<Point>
{
  auto operator()(const Point & k) const -> std::size_t
  {
    string s = to_string(k.x) + "_" + to_string(k.y) + "_" + to_string(k.z) + "_" + to_string(k.w);

    return hash<string>()(s);
  }
};

auto rangeint(long long from, long long to) -> vector<long long>
{
  vector<long long> ret(to - from + 1);
  iota(begin(ret), end(ret), from);
  return ret;
}

auto rangeint2(long long from, long long to) -> vector<long long>
{
  LL                sizeN = abs(to - from) + 1;
  vector<long long> ret;

  ret.reserve(sizeN);
  int dir = to >= from ? 1 : -1;
  for (LL t = 0, v = from; t < sizeN; v += dir, ++t)
    ret.push_back(v);
  return ret;
}

template <typename V>
auto rangevec(V & t, long long from, long long to) -> V
{
  V    rt;
  auto r = rangeint(from, to);
  for (auto i : r)
  {
    if (i < t.size())
      rt.insert(end(rt), t[i]);
    else
      break;
  }
  return rt;
}

template <typename T>
auto addvec(const vector<T> & a, const vector<T> & b) -> vector<T>
{
  vector<T> ret;
  ret.reserve(a.size() + b.size());
  for (auto i : a)
    ret.push_back(i);
  for (auto i : b)
    ret.push_back(i);
  return ret;
}

template <class T, class F>
void for_each(const T & c, F func)
{
  for_each(begin(c), end(c), func);
}

template <class T, class V>
auto contains(const T & c, const V & v) -> bool
{
  return find(begin(c), end(c), v) != end(c);
}

template <class T, class S>
void printvec(const vector<T> & v, S & stream)
{
  stream << endl;
  for (auto & el : v)
    stream << el << ", ";
}

template <class T, class S>
void printset(const set<T> & v, S & stream)
{
  stream << endl;
  for (auto & el : v)
    stream << el << " ";
}

template <class T, class S>
void printset(unordered_set<T> & v, S & stream)
{
  stream << endl;
  for (auto & el : v)
    stream << el << " ";
}

template <class T, class U, class S>
void printmap(map<T, U> & m, S & stream)
{
  stream << endl;
  for (auto & el : m)
  {
    stream << "[" << el.first << "] = " << el.second << endl;
  }
}

template <class T, class U, class S>
void printmap(unordered_map<T, U> & m, S & stream)
{
  stream << endl;
  for (auto & el : m)
  {
    stream << "[" << el.first << "] = " << el.second << endl;
  }
}

template <class T>
class Graph
{
private:
  using WeightNodePair = pair<int, int>;

  int vertexCount;

  vector<list<pair<int, int>>> adjacency;

  void DoTopoSort(int v, bool visited[], stack<int> & Stack)
  {
    // Mark the current node as visited.
    visited[v] = true;

    // Recur for all the vertices adjacent to this vertex
    list<pair<int, int>>::iterator i;
    for (i = adjacency[v].begin(); i != adjacency[v].end(); ++i)
      if (!visited[i->first])
        DoTopoSort(i->first, visited, Stack);

    // Push current vertex to stack which stores result
    Stack.push(v);
  }

  objmap<T> mapper;

  void AddEdge(int node1, int node2, int weight) { adjacency[node1].emplace_back(node2, weight); }

  void AddOrIncrementEdge(int node1, int node2, int weight)
  {
    for (auto it = begin(adjacency[node1]); it != end(adjacency[node1]); ++it)
    {
      if (it->first == node2)
      {
        it->second += weight;
        return;
      }
    }
    AddEdge(node1, node2, weight);
  }

  auto GetEdgesFrom(int node1) -> vector<int>
  {
    vector<int> ret;
    for (auto it = begin(adjacency[node1]); it != end(adjacency[node1]); ++it)
    {
      ret.push_back(it->first);
    }
    return ret;
  }

  auto GetEdgesTo(int node1) -> vector<int>
  {
    vector<int> ret;
    for (auto it : rangeint(0, vertexCount - 1))
    {
      for (auto vv = begin(adjacency[it]); vv != end(adjacency[it]); ++vv)
      {
        if (vv->first == node1)
          ret.push_back(it);
      }
    }
    return ret;
  }

  void AddEdgeSymmetrical(int node1, int node2, int weight)
  {
    adjacency[node1].push_back(make_pair(node2, weight));
    adjacency[node2].push_back(make_pair(node1, weight));
  }

  void ClearEdge(int node1, int node2)
  {
    for (auto node1edge = adjacency[node1].begin(); node1edge != adjacency[node1].end();
         node1edge++)
    {
      if (node1edge->first == node2)
      {
        adjacency[node1].erase(node1edge);
        break;
      }
    }
    for (auto node2edge = adjacency[node2].begin(); node2edge != adjacency[node2].end();
         node2edge++)
    {
      if (node2edge->first == node1)
      {
        adjacency[node2].erase(node2edge);
        break;
      }
    }
  }

  void AddAdjacencyMatrix(DynamicMap<int> & aMap)
  {
    adjacency.clear();
    adjacency.resize(vertexCount);

    for (int i = aMap.min_x; i <= aMap.max_x; ++i)
    {
      for (int j = aMap.min_y; j <= aMap.max_y; ++j)
      {
        int val = 0;
        if (i == j)
          continue;

        if (aMap.at({ i, j }, &val))
        {
          if (val > 0)
          {
            AddEdge(i, j, val);
          }
        }
      }
    }
  }

  auto GetDistances(int src) -> map<int, int>
  {
    priority_queue<WeightNodePair, vector<WeightNodePair>, greater<WeightNodePair>> pq;

    vector<int> dist(vertexCount, numeric_limits<int>::max() - 1);

    pq.push(make_pair(0, src));
    dist[src] = 0;

    while (!pq.empty())
    {
      int u = pq.top().second;
      pq.pop();

      for (auto i = adjacency[u].begin(); i != adjacency[u].end(); ++i)
      {
        int v      = (*i).first;
        int weight = (*i).second;

        if (dist[v] > dist[u] + weight)
        {
          dist[v] = dist[u] + weight;
          pq.push(make_pair(dist[v], v));
        }
      }
    }

    map<int, int> distanceMap;
    for (int i = 0; i < vertexCount; ++i)
      distanceMap[i] = dist[i];
    return distanceMap;
  }

  auto GetShortestPath(int src, int dest) -> vector<int>
  {
    priority_queue<WeightNodePair, vector<WeightNodePair>, greater<>> pq;

    vector<int> dist(vertexCount, numeric_limits<int>::max() - 1);
    vector<int> prev(vertexCount, -1);

    pq.push(make_pair(0, src));
    dist[src] = 0;

    while (!pq.empty())
    {
      int u = pq.top().second;
      pq.pop();
      if (u == dest)
      {
        break;
      }

      for (auto i = adjacency[u].begin(); i != adjacency[u].end(); ++i)
      {
        int v      = (*i).first;
        int weight = (*i).second;

        if (dist[v] > dist[u] + weight)
        {
          dist[v] = dist[u] + weight;
          pq.push(make_pair(dist[v], v));
          prev[v] = u;
        }
      }
    }

    vector<int> retNodes;
    int         u = dest;
    while (prev[u] >= 0 || u == src)
    {
      retNodes.insert(begin(retNodes), u);
      u = prev[u];
      if (u < 0)
      {
        break;
      }
    }

    return retNodes;
  }

  auto SortTopo() -> vector<int>
  {
    stack<int> Stack;

    // Mark all the vertices as not visited
    bool * visited = new bool[vertexCount];
    for (int i = 0; i < vertexCount; i++)
      visited[i] = false;

    // Call the recursive helper function to store Topological
    // Sort starting from all vertices one by one
    for (int i = 0; i < vertexCount; i++)
      if (visited[i] == false)
        DoTopoSort(i, visited, Stack);

    vector<int> ret;
    // Print contents of stack
    while (Stack.empty() == false)
    {
      ret.push_back(Stack.top());
      Stack.pop();
    }
    return ret;
  }

  auto GetAllPaths(int from, int to) -> vector<vector<int>>
  {
    vector<vector<int>> ret;

    bool * visited = new bool[vertexCount];

    int * path       = new int[vertexCount];
    int   path_index = 0;

    for (int i = 0; i < vertexCount; i++)
      visited[i] = false;

    GetAllPathsUtil(from, to, visited, path, path_index, ret);

    return ret;
  }

  void GetAllPathsUtil(
    int u, int d, bool visited[], int path[], int & path_index, vector<vector<int>> & bucket)
  {
    visited[u]       = true;
    path[path_index] = u;
    path_index++;

    if (u == d)
    {
      vector<int> newPath;
      for (int i = 0; i < path_index; i++)
        newPath.push_back(path[i]);
      bucket.push_back(newPath);
    }
    else
    {
      for (auto i = adjacency[u].begin(); i != adjacency[u].end(); ++i)
        if (!visited[i->first])
          GetAllPathsUtil(i->first, d, visited, path, path_index, bucket);
    }

    path_index--;
    visited[u] = false;
  }

  auto CountPaths(int from, int to) -> LL
  {
    LL pathCount = 0;
    CountPathsUtil(from, to, pathCount);
    return pathCount;
  }

  void CountPathsUtil(int u, int d, LL & pathCount)
  {
    if (u == d)
      pathCount++;
    else
    {
      for (auto i = adjacency[u].begin(); i != adjacency[u].end(); ++i)
        CountPathsUtil(i->first, d, pathCount);
    }
  }

public:
  Graph(int aVertexCount)
  {
    this->vertexCount = aVertexCount;
    adjacency.resize(aVertexCount);
  }

  void AddEdge(const T & node1, const T & node2, int weight)
  {
    return AddEdge(mapper[node1], mapper[node2], weight);
  }

  void AddOrIncrementEdge(const T & node1, const T & node2, int weight)
  {
    AddOrIncrementEdge(mapper[node1], mapper[node2], weight);
  }

  auto GetEdgesFrom(const T & node1) -> vector<T>
  {
    return mapper.translate(GetEdgesFrom(mapper[node1]));
  }

  auto GetEdgesTo(const T & node1) -> vector<T>
  {
    return mapper.translate(GetEdgesTo(mapper[node1]));
  }

  void AddEdgeSymmetrical(const T & node1, const T & node2, int weight)
  {
    AddEdgeSymmetrical(mapper[node1], mapper[node2], weight);
  }

  void ClearEdge(const T & node1, const T & node2)
  {
    return ClearEdge(mapper[node1], mapper[node2]);
  }

  auto GetDistances(const T & src) -> map<T, int>
  {
    map<T, int> ret;
    auto        dist = GetDistances(mapper[src]);
    for (auto d : dist)
      ret[mapper.translate(d.first)] = d.second;
    return ret;
  }

  auto GetShortestPath(const T & src, const T & dest) -> vector<T>
  {
    auto path = GetShortestPath(mapper[src], mapper[dest]);
    return mapper.translate(path);
  }

  auto SortTopologically() -> vector<T> { return mapper.translate(SortTopo()); }

  auto CountPaths(const T & s, const T & d) -> LL { return CountPaths(mapper[s], mapper[d]); }

  auto GetAllPaths(const T & from, const T & to) -> vector<vector<T>>
  {
    auto              paths = GetAllPaths(mapper[from], mapper[to]);
    vector<vector<T>> ret;
    for (auto path : paths)
      ret.push_back(mapper.translate(path));
    return ret;
  }
};

unordered_set<LL> getPrimeFactors(LL n)
{
  unordered_set<LL> ret;
  while (n % 2 == 0)
  {
    ret.insert(2);
    n = n / 2;
  }

  for (LL i = 3; i <= sqrt(n); i = i + 2)
  {
    while (n % i == 0)
    {
      ret.insert(i);
      n = n / i;
    }
  }

  if (n > 2)
    ret.insert(n);
  return ret;
}

auto gcd(long long a, long long b) -> long long
{
  while (true)
  {
    if (a == 0)
    {
      return b;
    }
    b %= a;
    if (b == 0)
    {
      return a;
    }
    a %= b;
  }
}

auto lcm(long long a, long long b) -> long long
{
  long long g = gcd(a, b);
  return g != 0 ? (a / g * b) : 0;
}

auto modInverse(long long a, long long m) -> long long
{
  long long m0 = m;
  long long y  = 0;
  long long x  = 1;

  if (m == 1)
  {
    return 0;
  }

  while (a > 1)
  {
    // q is quotient
    long long q = a / m;
    long long t = m;

    // m is remainder now, process same as
    // Euclid's algo
    m = a % m;
    a = t;
    t = y;

    // Update y and x
    y = x - q * y;
    x = t;
  }

  // Make x positive
  if (x < 0)
  {
    x += m0;
  }

  return x;
}

auto getChineseRemainderMinNumber(const vector<pair<LL, LL>> & numbersAndRemainders) -> LL
{
  LL allProduct = 1;
  for (auto numAndRemainder : numbersAndRemainders)
  {
    allProduct *= numAndRemainder.first;
  }

  LL result = 0;
  for (auto numAndRemainder : numbersAndRemainders)
  {
    LL pp = allProduct / numAndRemainder.first;
    result += numAndRemainder.second * modInverse(pp, numAndRemainder.first) * pp;
  }

  return result % allProduct;
}

/* Iterative Function to calculate (x^y)%p in O(log y) */
auto power(long long x, long long y, long long p) -> long long
{
  long long res = 1;  // Initialize result

  x = x % p;  // Update x if it is more than or
              // equal to p

  while (y > 0)
  {
    // If y is odd, multiply x with result
    if ((y & 1) != 0)
    {
      res = (res * x) % p;
    }

    // y must be even now
    y = y >> 1;  // y = y/2
    x = (x * x) % p;
  }
  return res;
}

void toConsole(Point p, const string & s)
{
#ifdef _MSC_VER
  DWORD  dw;
  COORD  here;
  HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  here.X         = (SHORT)p.x;
  here.Y         = (SHORT)p.y;
  WriteConsoleOutputCharacter(hStdOut, s.c_str(), (DWORD)s.size(), here, &dw);
#endif
#ifdef __APPLE__
  assert(!"Unsupported on current platform");
#endif
};

auto binsearch(long long left, long long right, long long find, function<long long(long long)> func)
  -> long long
{
  while (right > left + 1)
  {
    long long searchPoint = left + (right - left) / 2;
    long long res         = func(searchPoint);
    if (res > find)
    {
      right = searchPoint;
    }
    if (res < find)
    {
      left = searchPoint;
    }
  }
  return left;
}

template <class KT, class VT>
auto findInMapByValue(map<KT, VT> & m, VT & val)
{
  auto it = find_if(begin(m), end(m),
                    [&val](const auto & it)
                    {
                      return it.second == val;
                    });
  if (it != end(m))
  {
    return it;
  }
  return end(m);
}

//--------------------------------------

#ifdef __APPLE__

#define KINPUT   "/Users/gabriel/repos/aoc/inputs/Day"
#define KOUTPUT  "/Users/gabriel/repos/aoc/output/output.txt"
#define KVERBOSE "/Users/gabriel/repos/aoc/output/verbose.txt"

#endif

#ifdef _MSC_VER

#define KINPUT   "C:\\repos\\aoc\\inputs\\Day"
#define KOUTPUT  "C:\\repos\\aoc\\output\\out.txt"
#define KVERBOSE "C:\\repos\\aoc\\output\\verbose.txt"

#endif
