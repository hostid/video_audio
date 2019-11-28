#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTimer>
#include <QMutex>

namespace Ui {
class MainWindow;
}
struct libvlc_media_track_info_t;
struct libvlc_media_t;
struct libvlc_instance_t;
struct libvlc_media_player_t;
struct libvlc_event_t;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool load(const QString &filepath);
    void play();
    void pause();
    void stop();
    bool loadVlc(const QString &filepath);
    void freeVlc();

protected:
    static void vlcEvents(const libvlc_event_t *ev, void *param);
private slots:
    void on_pushButton_clicked();
    void on_pB_Stop_clicked();
    void on_pB_Open_clicked();

private:
    Ui::MainWindow *ui;

    libvlc_instance_t *m_vlcInstance = Q_NULLPTR;
    libvlc_media_t *m_media = Q_NULLPTR;
    libvlc_media_player_t *m_mediaPlayer = Q_NULLPTR;

    QFileDialog *m_fileDialog = Q_NULLPTR;
    QTimer *m_timer = Q_NULLPTR;

    QMutex m_mutex;
    qint64 m_duration = 0;
    bool m_bPlaying = false;
};

#endif // MAINWINDOW_H
