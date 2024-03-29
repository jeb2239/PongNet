// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_STATE_PONG_NET_STATE_H_
#define FLATBUFFERS_GENERATED_STATE_PONG_NET_STATE_H_

#include "flatbuffers/flatbuffers.h"

namespace Pong {
namespace Net {
namespace State {

struct Rect;

struct Ball;
struct BallBuilder;

struct Player;
struct PlayerBuilder;

struct Game;
struct GameBuilder;

struct PlayerLogin;
struct PlayerLoginBuilder;

struct PlayerLogout;
struct PlayerLogoutBuilder;

struct PlayerLoginAck;
struct PlayerLoginAckBuilder;

struct Message;
struct MessageBuilder;

enum PacketType : uint8_t {
  PacketType_NONE = 0,
  PacketType_Login = 1,
  PacketType_LoginAck = 2,
  PacketType_ReplicationData = 3,
  PacketType_Logout = 4,
  PacketType_MIN = PacketType_NONE,
  PacketType_MAX = PacketType_Logout
};

inline const PacketType (&EnumValuesPacketType())[5] {
  static const PacketType values[] = {
    PacketType_NONE,
    PacketType_Login,
    PacketType_LoginAck,
    PacketType_ReplicationData,
    PacketType_Logout
  };
  return values;
}

inline const char * const *EnumNamesPacketType() {
  static const char * const names[6] = {
    "NONE",
    "Login",
    "LoginAck",
    "ReplicationData",
    "Logout",
    nullptr
  };
  return names;
}

inline const char *EnumNamePacketType(PacketType e) {
  if (flatbuffers::IsOutRange(e, PacketType_NONE, PacketType_Logout)) return "";
  const size_t index = static_cast<size_t>(e);
  return EnumNamesPacketType()[index];
}

template<typename T> struct PacketTypeTraits {
  static const PacketType enum_value = PacketType_NONE;
};

template<> struct PacketTypeTraits<Pong::Net::State::PlayerLogin> {
  static const PacketType enum_value = PacketType_Login;
};

template<> struct PacketTypeTraits<Pong::Net::State::PlayerLoginAck> {
  static const PacketType enum_value = PacketType_LoginAck;
};

template<> struct PacketTypeTraits<Pong::Net::State::Game> {
  static const PacketType enum_value = PacketType_ReplicationData;
};

template<> struct PacketTypeTraits<Pong::Net::State::PlayerLogout> {
  static const PacketType enum_value = PacketType_Logout;
};

bool VerifyPacketType(flatbuffers::Verifier &verifier, const void *obj, PacketType type);
bool VerifyPacketTypeVector(flatbuffers::Verifier &verifier, const flatbuffers::Vector<flatbuffers::Offset<void>> *values, const flatbuffers::Vector<uint8_t> *types);

FLATBUFFERS_MANUALLY_ALIGNED_STRUCT(4) Rect FLATBUFFERS_FINAL_CLASS {
 private:
  int32_t x_;
  int32_t y_;
  int32_t w_;
  int32_t h_;

 public:
  Rect()
      : x_(0),
        y_(0),
        w_(0),
        h_(0) {
  }
  Rect(int32_t _x, int32_t _y, int32_t _w, int32_t _h)
      : x_(flatbuffers::EndianScalar(_x)),
        y_(flatbuffers::EndianScalar(_y)),
        w_(flatbuffers::EndianScalar(_w)),
        h_(flatbuffers::EndianScalar(_h)) {
  }
  int32_t x() const {
    return flatbuffers::EndianScalar(x_);
  }
  int32_t y() const {
    return flatbuffers::EndianScalar(y_);
  }
  int32_t w() const {
    return flatbuffers::EndianScalar(w_);
  }
  int32_t h() const {
    return flatbuffers::EndianScalar(h_);
  }
};
FLATBUFFERS_STRUCT_END(Rect, 16);

struct Ball FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef BallBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_VX = 4,
    VT_VY = 6,
    VT_SPEED = 8,
    VT_RECT = 10
  };
  float vx() const {
    return GetField<float>(VT_VX, 0.0f);
  }
  float vy() const {
    return GetField<float>(VT_VY, 0.0f);
  }
  float speed() const {
    return GetField<float>(VT_SPEED, 0.0f);
  }
  const Pong::Net::State::Rect *rect() const {
    return GetStruct<const Pong::Net::State::Rect *>(VT_RECT);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<float>(verifier, VT_VX) &&
           VerifyField<float>(verifier, VT_VY) &&
           VerifyField<float>(verifier, VT_SPEED) &&
           VerifyField<Pong::Net::State::Rect>(verifier, VT_RECT) &&
           verifier.EndTable();
  }
};

struct BallBuilder {
  typedef Ball Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_vx(float vx) {
    fbb_.AddElement<float>(Ball::VT_VX, vx, 0.0f);
  }
  void add_vy(float vy) {
    fbb_.AddElement<float>(Ball::VT_VY, vy, 0.0f);
  }
  void add_speed(float speed) {
    fbb_.AddElement<float>(Ball::VT_SPEED, speed, 0.0f);
  }
  void add_rect(const Pong::Net::State::Rect *rect) {
    fbb_.AddStruct(Ball::VT_RECT, rect);
  }
  explicit BallBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<Ball> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Ball>(end);
    return o;
  }
};

inline flatbuffers::Offset<Ball> CreateBall(
    flatbuffers::FlatBufferBuilder &_fbb,
    float vx = 0.0f,
    float vy = 0.0f,
    float speed = 0.0f,
    const Pong::Net::State::Rect *rect = 0) {
  BallBuilder builder_(_fbb);
  builder_.add_rect(rect);
  builder_.add_speed(speed);
  builder_.add_vy(vy);
  builder_.add_vx(vx);
  return builder_.Finish();
}

struct Player FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef PlayerBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_POS = 4,
    VT_SPEED = 6,
    VT_SCORE = 8
  };
  const Pong::Net::State::Rect *pos() const {
    return GetStruct<const Pong::Net::State::Rect *>(VT_POS);
  }
  int32_t speed() const {
    return GetField<int32_t>(VT_SPEED, 0);
  }
  int32_t score() const {
    return GetField<int32_t>(VT_SCORE, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<Pong::Net::State::Rect>(verifier, VT_POS) &&
           VerifyField<int32_t>(verifier, VT_SPEED) &&
           VerifyField<int32_t>(verifier, VT_SCORE) &&
           verifier.EndTable();
  }
};

struct PlayerBuilder {
  typedef Player Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_pos(const Pong::Net::State::Rect *pos) {
    fbb_.AddStruct(Player::VT_POS, pos);
  }
  void add_speed(int32_t speed) {
    fbb_.AddElement<int32_t>(Player::VT_SPEED, speed, 0);
  }
  void add_score(int32_t score) {
    fbb_.AddElement<int32_t>(Player::VT_SCORE, score, 0);
  }
  explicit PlayerBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<Player> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Player>(end);
    return o;
  }
};

inline flatbuffers::Offset<Player> CreatePlayer(
    flatbuffers::FlatBufferBuilder &_fbb,
    const Pong::Net::State::Rect *pos = 0,
    int32_t speed = 0,
    int32_t score = 0) {
  PlayerBuilder builder_(_fbb);
  builder_.add_score(score);
  builder_.add_speed(speed);
  builder_.add_pos(pos);
  return builder_.Finish();
}

struct Game FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef GameBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_PLAYER1 = 4,
    VT_PLAYER2 = 6,
    VT_BALL = 8
  };
  const Pong::Net::State::Player *player1() const {
    return GetPointer<const Pong::Net::State::Player *>(VT_PLAYER1);
  }
  const Pong::Net::State::Player *player2() const {
    return GetPointer<const Pong::Net::State::Player *>(VT_PLAYER2);
  }
  const Pong::Net::State::Ball *ball() const {
    return GetPointer<const Pong::Net::State::Ball *>(VT_BALL);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_PLAYER1) &&
           verifier.VerifyTable(player1()) &&
           VerifyOffset(verifier, VT_PLAYER2) &&
           verifier.VerifyTable(player2()) &&
           VerifyOffset(verifier, VT_BALL) &&
           verifier.VerifyTable(ball()) &&
           verifier.EndTable();
  }
};

struct GameBuilder {
  typedef Game Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_player1(flatbuffers::Offset<Pong::Net::State::Player> player1) {
    fbb_.AddOffset(Game::VT_PLAYER1, player1);
  }
  void add_player2(flatbuffers::Offset<Pong::Net::State::Player> player2) {
    fbb_.AddOffset(Game::VT_PLAYER2, player2);
  }
  void add_ball(flatbuffers::Offset<Pong::Net::State::Ball> ball) {
    fbb_.AddOffset(Game::VT_BALL, ball);
  }
  explicit GameBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<Game> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Game>(end);
    return o;
  }
};

inline flatbuffers::Offset<Game> CreateGame(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<Pong::Net::State::Player> player1 = 0,
    flatbuffers::Offset<Pong::Net::State::Player> player2 = 0,
    flatbuffers::Offset<Pong::Net::State::Ball> ball = 0) {
  GameBuilder builder_(_fbb);
  builder_.add_ball(ball);
  builder_.add_player2(player2);
  builder_.add_player1(player1);
  return builder_.Finish();
}

struct PlayerLogin FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef PlayerLoginBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_PLAYERID = 4,
    VT_PLAYERNAME = 6
  };
  uint8_t playerId() const {
    return GetField<uint8_t>(VT_PLAYERID, 0);
  }
  const flatbuffers::String *playerName() const {
    return GetPointer<const flatbuffers::String *>(VT_PLAYERNAME);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint8_t>(verifier, VT_PLAYERID) &&
           VerifyOffset(verifier, VT_PLAYERNAME) &&
           verifier.VerifyString(playerName()) &&
           verifier.EndTable();
  }
};

struct PlayerLoginBuilder {
  typedef PlayerLogin Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_playerId(uint8_t playerId) {
    fbb_.AddElement<uint8_t>(PlayerLogin::VT_PLAYERID, playerId, 0);
  }
  void add_playerName(flatbuffers::Offset<flatbuffers::String> playerName) {
    fbb_.AddOffset(PlayerLogin::VT_PLAYERNAME, playerName);
  }
  explicit PlayerLoginBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<PlayerLogin> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<PlayerLogin>(end);
    return o;
  }
};

inline flatbuffers::Offset<PlayerLogin> CreatePlayerLogin(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint8_t playerId = 0,
    flatbuffers::Offset<flatbuffers::String> playerName = 0) {
  PlayerLoginBuilder builder_(_fbb);
  builder_.add_playerName(playerName);
  builder_.add_playerId(playerId);
  return builder_.Finish();
}

inline flatbuffers::Offset<PlayerLogin> CreatePlayerLoginDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint8_t playerId = 0,
    const char *playerName = nullptr) {
  auto playerName__ = playerName ? _fbb.CreateString(playerName) : 0;
  return Pong::Net::State::CreatePlayerLogin(
      _fbb,
      playerId,
      playerName__);
}

struct PlayerLogout FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef PlayerLogoutBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_PLAYERID = 4
  };
  uint8_t playerId() const {
    return GetField<uint8_t>(VT_PLAYERID, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint8_t>(verifier, VT_PLAYERID) &&
           verifier.EndTable();
  }
};

struct PlayerLogoutBuilder {
  typedef PlayerLogout Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_playerId(uint8_t playerId) {
    fbb_.AddElement<uint8_t>(PlayerLogout::VT_PLAYERID, playerId, 0);
  }
  explicit PlayerLogoutBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<PlayerLogout> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<PlayerLogout>(end);
    return o;
  }
};

inline flatbuffers::Offset<PlayerLogout> CreatePlayerLogout(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint8_t playerId = 0) {
  PlayerLogoutBuilder builder_(_fbb);
  builder_.add_playerId(playerId);
  return builder_.Finish();
}

struct PlayerLoginAck FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef PlayerLoginAckBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_OPPONENTID = 4
  };
  uint8_t opponentId() const {
    return GetField<uint8_t>(VT_OPPONENTID, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint8_t>(verifier, VT_OPPONENTID) &&
           verifier.EndTable();
  }
};

struct PlayerLoginAckBuilder {
  typedef PlayerLoginAck Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_opponentId(uint8_t opponentId) {
    fbb_.AddElement<uint8_t>(PlayerLoginAck::VT_OPPONENTID, opponentId, 0);
  }
  explicit PlayerLoginAckBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<PlayerLoginAck> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<PlayerLoginAck>(end);
    return o;
  }
};

inline flatbuffers::Offset<PlayerLoginAck> CreatePlayerLoginAck(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint8_t opponentId = 0) {
  PlayerLoginAckBuilder builder_(_fbb);
  builder_.add_opponentId(opponentId);
  return builder_.Finish();
}

struct Message FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef MessageBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_SENDTO = 4,
    VT_TYPE_TYPE = 6,
    VT_TYPE = 8
  };
  uint64_t sendTo() const {
    return GetField<uint64_t>(VT_SENDTO, 0);
  }
  Pong::Net::State::PacketType type_type() const {
    return static_cast<Pong::Net::State::PacketType>(GetField<uint8_t>(VT_TYPE_TYPE, 0));
  }
  const void *type() const {
    return GetPointer<const void *>(VT_TYPE);
  }
  template<typename T> const T *type_as() const;
  const Pong::Net::State::PlayerLogin *type_as_Login() const {
    return type_type() == Pong::Net::State::PacketType_Login ? static_cast<const Pong::Net::State::PlayerLogin *>(type()) : nullptr;
  }
  const Pong::Net::State::PlayerLoginAck *type_as_LoginAck() const {
    return type_type() == Pong::Net::State::PacketType_LoginAck ? static_cast<const Pong::Net::State::PlayerLoginAck *>(type()) : nullptr;
  }
  const Pong::Net::State::Game *type_as_ReplicationData() const {
    return type_type() == Pong::Net::State::PacketType_ReplicationData ? static_cast<const Pong::Net::State::Game *>(type()) : nullptr;
  }
  const Pong::Net::State::PlayerLogout *type_as_Logout() const {
    return type_type() == Pong::Net::State::PacketType_Logout ? static_cast<const Pong::Net::State::PlayerLogout *>(type()) : nullptr;
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint64_t>(verifier, VT_SENDTO) &&
           VerifyField<uint8_t>(verifier, VT_TYPE_TYPE) &&
           VerifyOffset(verifier, VT_TYPE) &&
           VerifyPacketType(verifier, type(), type_type()) &&
           verifier.EndTable();
  }
};

template<> inline const Pong::Net::State::PlayerLogin *Message::type_as<Pong::Net::State::PlayerLogin>() const {
  return type_as_Login();
}

template<> inline const Pong::Net::State::PlayerLoginAck *Message::type_as<Pong::Net::State::PlayerLoginAck>() const {
  return type_as_LoginAck();
}

template<> inline const Pong::Net::State::Game *Message::type_as<Pong::Net::State::Game>() const {
  return type_as_ReplicationData();
}

template<> inline const Pong::Net::State::PlayerLogout *Message::type_as<Pong::Net::State::PlayerLogout>() const {
  return type_as_Logout();
}

struct MessageBuilder {
  typedef Message Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_sendTo(uint64_t sendTo) {
    fbb_.AddElement<uint64_t>(Message::VT_SENDTO, sendTo, 0);
  }
  void add_type_type(Pong::Net::State::PacketType type_type) {
    fbb_.AddElement<uint8_t>(Message::VT_TYPE_TYPE, static_cast<uint8_t>(type_type), 0);
  }
  void add_type(flatbuffers::Offset<void> type) {
    fbb_.AddOffset(Message::VT_TYPE, type);
  }
  explicit MessageBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<Message> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Message>(end);
    return o;
  }
};

inline flatbuffers::Offset<Message> CreateMessage(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint64_t sendTo = 0,
    Pong::Net::State::PacketType type_type = Pong::Net::State::PacketType_NONE,
    flatbuffers::Offset<void> type = 0) {
  MessageBuilder builder_(_fbb);
  builder_.add_sendTo(sendTo);
  builder_.add_type(type);
  builder_.add_type_type(type_type);
  return builder_.Finish();
}

inline bool VerifyPacketType(flatbuffers::Verifier &verifier, const void *obj, PacketType type) {
  switch (type) {
    case PacketType_NONE: {
      return true;
    }
    case PacketType_Login: {
      auto ptr = reinterpret_cast<const Pong::Net::State::PlayerLogin *>(obj);
      return verifier.VerifyTable(ptr);
    }
    case PacketType_LoginAck: {
      auto ptr = reinterpret_cast<const Pong::Net::State::PlayerLoginAck *>(obj);
      return verifier.VerifyTable(ptr);
    }
    case PacketType_ReplicationData: {
      auto ptr = reinterpret_cast<const Pong::Net::State::Game *>(obj);
      return verifier.VerifyTable(ptr);
    }
    case PacketType_Logout: {
      auto ptr = reinterpret_cast<const Pong::Net::State::PlayerLogout *>(obj);
      return verifier.VerifyTable(ptr);
    }
    default: return true;
  }
}

inline bool VerifyPacketTypeVector(flatbuffers::Verifier &verifier, const flatbuffers::Vector<flatbuffers::Offset<void>> *values, const flatbuffers::Vector<uint8_t> *types) {
  if (!values || !types) return !values && !types;
  if (values->size() != types->size()) return false;
  for (flatbuffers::uoffset_t i = 0; i < values->size(); ++i) {
    if (!VerifyPacketType(
        verifier,  values->Get(i), types->GetEnum<PacketType>(i))) {
      return false;
    }
  }
  return true;
}

inline const Pong::Net::State::Game *GetGame(const void *buf) {
  return flatbuffers::GetRoot<Pong::Net::State::Game>(buf);
}

inline const Pong::Net::State::Game *GetSizePrefixedGame(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<Pong::Net::State::Game>(buf);
}

inline bool VerifyGameBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<Pong::Net::State::Game>(nullptr);
}

inline bool VerifySizePrefixedGameBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<Pong::Net::State::Game>(nullptr);
}

inline void FinishGameBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<Pong::Net::State::Game> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedGameBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<Pong::Net::State::Game> root) {
  fbb.FinishSizePrefixed(root);
}

}  // namespace State
}  // namespace Net
}  // namespace Pong

#endif  // FLATBUFFERS_GENERATED_STATE_PONG_NET_STATE_H_
