#include <windows.h>
#include <vlc/vlc.h>
#include <time.h>

int main(int argc, char* argv[])
{
	libvlc_instance_t *     vlc_ins = NULL;
	libvlc_media_player_t * vlc_player = NULL;
	libvlc_media_t *        vlc_media = NULL;

	const char * vlc_args[] =
	{
		"-I",
		"dummy",
		"--ignore-config",
		"--extraintf=logger",
		"--verbose=2",
	};

	// ����һ��VLCʵ��
	vlc_ins = libvlc_new(sizeof(vlc_args) / sizeof(vlc_args[0]), vlc_args);
	if (vlc_ins != NULL)
	{
		// ����һ��VLC������
		vlc_player = libvlc_media_player_new(vlc_ins);
		if (vlc_player != NULL)
		{

			vlc_media = libvlc_media_new_location(vlc_ins, "rtsp://192.168.0.193:8554/123");

			// ͨ���ļ�·������һ��ý��ʵ��,�������ҵĲ����ļ�
			//vlc_media = libvlc_media_new_path(vlc_ins, "d:\\test.avi");
			if (vlc_media != NULL)
			{
				// ����ý��ʵ��
				libvlc_media_parse(vlc_media);
				// ��ȡý���ļ��Ĳ��ų���,  ���� ms
				libvlc_time_t duration = libvlc_media_get_duration(vlc_media);

				// �˴��ǻ�ȡý������������Ƶ����Ƶ���Լ��������͵Ĺ����Ϣ
				libvlc_media_track_info_t *media_tracks = NULL;
				int trackCount = libvlc_media_get_tracks_info(vlc_media, &media_tracks);
				// �������ͷ��ڴ棬���Ҳ��Ե�ʱ��������⣬��û��ϸ�о���Ϊ��
				// free(media_tracks);  // crash?

				// �Ѵ򿪵�ý���ļ����ø�������
				libvlc_media_player_set_media(vlc_player, vlc_media);

				// ��Ϊ��windowsϵͳ��������Ҫ����һ��HWND����������Ϊ����,�����ֱ��ʹ�����洰��,������ǲ���
				libvlc_media_player_set_hwnd(vlc_player, ::GetDesktopWindow());
				// ��ʼ������Ƶ
				libvlc_media_player_play(vlc_player);

				// �������Ϊ�˴�ӡһЩ��Ϣ����,20����˳�
				time_t last_time = time(NULL);
				while ((time(NULL) < (last_time + 200)))
				{
					Sleep(10);
					// ��ȡ��ǰ����λ��
					libvlc_time_t play_time = libvlc_media_player_get_time(vlc_player);
					printf("playing time : %lld ms\r", (__int64)(play_time));

					// ��ȡý���״̬
					// libvlc_state_t media_state = libvlc_media_get_state(vlc_media);
					// printf("\nmedia state : %d\n", (int)(media_state));
				}
				// ֹͣ
				libvlc_media_player_stop(vlc_player);
				// �ͷ�
				libvlc_media_release(vlc_media);
			}
			// �ͷ�
			libvlc_media_player_release(vlc_player);
		}
		// �ͷ�
		libvlc_release(vlc_ins);
	}
	return 0;
}