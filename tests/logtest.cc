#include <gtest/gtest.h>
#include <usermsg/usermsg.h>
#include <usermsg/usermsgman.h>
#include <usermsg/usermsgstg.h>

#include <QByteArray>
#include <QSettings>
#include <QFileInfo>
#include <QTemporaryFile>
#include <QApplication>
#include <QRegularExpression>


class TestLog : public ::testing::Test {
    QCoreApplication * app;
public:

    TestLog () {}

    virtual ~TestLog () {}

    void SetUp(){
        int argc = 1;
        const char * argv[] = {"test"};
        app = new QCoreApplication (argc, (char**)argv);
        UserMsgMan::init ();
    }
    void TearDown(){
        UserMsgMan::end ();
        delete app;
    }

};

bool b_cmp_apparently_equal (const QString & s1, const QString & s2)
{
    int i1 = s1.length ();
    int i2 = s2.length ();
    if (i1 != i2) return false;
    for (int i = i; i < i1; ++i) {
        if (s1.at (i) != s2.at(i)) {
            return false;
        }
    }
    return true;
}

QString tempFile ()
{
    QTemporaryFile tmpf;
    bool b = tmpf.open ();
    QString tmp_file = tmpf.fileName ();
    tmpf.close ();
    tmpf.remove ();
    return tmp_file;
}

TEST_F(TestLog, autoset) {
    UserMsgMan::autosetLogFile ("testxyz");
    QString log_file = UserMsgMan::logFile ();
    QFileInfo fi (log_file);
    EXPECT_TRUE(fi.exists ());
    EXPECT_TRUE(fi.fileName ().contains ("testxyz"));
}


TEST_F(TestLog, set) {

    QString tmp_file = tempFile ();

    UserMsgMan::setLogFile (tmp_file);
    QString log_file = UserMsgMan::logFile ();
    EXPECT_FALSE(log_file.isEmpty ());
    QFileInfo fi (log_file);
    EXPECT_TRUE(fi.exists ());
    EXPECT_TRUE(b_cmp_apparently_equal (fi.absoluteFilePath (), tmp_file));
    UserMsgMan::setLogFile ("");
    log_file = UserMsgMan::logFile ();
    EXPECT_TRUE(log_file.isEmpty ());

    QFile(tmp_file).remove ();
}

TEST_F(TestLog, log_content) {
    QString tmp_file = tempFile ();
    UserMsgMan::setLogFile (tmp_file);
    UserMsgMan::disable ();

    UserMsg um ("Title here");
    um.addErr ("Error here");
    um.addWar ("Warning here");
    um.addInfo ("Info here");
    um.addDbgErr ("DbgErr here");
    um.addDbgWar ("DbgWar here");
    um.addDbgInfo ("DbgInfo here");

    um.show ();

    UserMsg um2 ("Title here2");
    um2.addErr ("Error here2");
    um2.addWar ("Warning here2");
    um2.addInfo ("Info here2");
    um2.addDbgErr ("DbgErr here2");
    um2.addDbgWar ("DbgWar here2");
    um2.addDbgInfo ("DbgInfo here2");

    um2.show ();

    QFile tf(tmp_file);
    ASSERT_TRUE (tf.open (QIODevice::ReadOnly | QIODevice::Text));
    QString tcont = QString (tf.readAll ());

    EXPECT_TRUE(tcont.contains ("Title here"));
    EXPECT_TRUE(tcont.contains ("Error here"));
    EXPECT_TRUE(tcont.contains ("Warning here"));
    EXPECT_TRUE(tcont.contains ("Info here"));
    EXPECT_TRUE(tcont.contains ("DbgErr here"));
    EXPECT_TRUE(tcont.contains ("DbgWar here"));
    EXPECT_TRUE(tcont.contains ("DbgInfo here"));

    EXPECT_TRUE(tcont.contains ("Title here2"));
    EXPECT_TRUE(tcont.contains ("Error here2"));
    EXPECT_TRUE(tcont.contains ("Warning here2"));
    EXPECT_TRUE(tcont.contains ("Info here2"));
    EXPECT_TRUE(tcont.contains ("DbgErr here2"));
    EXPECT_TRUE(tcont.contains ("DbgWar here2"));
    EXPECT_TRUE(tcont.contains ("DbgInfo here2"));

    EXPECT_TRUE(tcont.contains ("debug   :"));
    EXPECT_TRUE(tcont.contains ("derror  :"));
    EXPECT_TRUE(tcont.contains ("dwarning:"));
    EXPECT_TRUE(tcont.contains ("error   :"));
    EXPECT_TRUE(tcont.contains ("info    :"));
    EXPECT_TRUE(tcont.contains ("warning :"));

    QRegularExpression date_rex ("[0-9]+-[0-9]+-[0-9]+T[0-9]+:[0-9]+:[0-9]+");
    EXPECT_TRUE(date_rex.match (tcont).hasMatch ());

    tf.close ();
    tf.remove ();
}
