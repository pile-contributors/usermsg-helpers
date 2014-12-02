#include <gtest/gtest.h>
#include <usermsg/usermsg.h>
#include <usermsg/usermsgman.h>
#include <usermsg/usermsgstg.h>

#include <QByteArray>
#include <QSettings>


class TestUsage : public ::testing::Test {

public:

    TestUsage () {}

    virtual ~TestUsage () {}

    void SetUp(){
        UserMsgMan::init ();
    }
    void TearDown(){
        UserMsgMan::end ();
    }

};

TEST_F(TestUsage, initial_state) {
    EXPECT_TRUE(UserMsgMan::isInitialized ());
    UserMsgMan::end ();
    EXPECT_FALSE(UserMsgMan::isInitialized ());
    UserMsgMan::init ();
}

TEST_F(TestUsage, settings_byte) {

    UserMsgStg stg = UserMsgMan::settings ();

    QByteArray ser_by = stg.toByteArray ();
    ASSERT_FALSE(ser_by.isNull ());

    UserMsgStg stg_copy;
    ASSERT_TRUE(stg_copy.fromByteArray (&ser_by));

    UserMsgMan::setSettings (stg_copy);
}

TEST_F(TestUsage, settings_qstg) {

    UserMsgStg stg = UserMsgMan::settings ();
    QSettings qstg;

    ASSERT_TRUE(stg.toQSettings (&qstg));

    UserMsgStg stg_copy;
    ASSERT_TRUE(stg_copy.fromQSettings (&qstg));

    UserMsgMan::setSettings (stg_copy);
}

TEST_F(TestUsage, enabled) {

    ASSERT_TRUE(UserMsgMan::isEnabled ());
    UserMsgMan::disable ();
    ASSERT_FALSE(UserMsgMan::isEnabled ());
    UserMsgMan::enable ();
    ASSERT_TRUE(UserMsgMan::isEnabled ());
}

TEST_F(TestUsage, constructors) {

    // default constructor
    UserMsg um_default;



    ASSERT_TRUE(UserMsgMan::isEnabled ());
    UserMsgMan::disable ();
    ASSERT_FALSE(UserMsgMan::isEnabled ());
    UserMsgMan::enable ();
    ASSERT_TRUE(UserMsgMan::isEnabled ());
}

