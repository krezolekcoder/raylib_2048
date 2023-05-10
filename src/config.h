#ifndef CONFIG_H
#define CONFIG_H


#define MAX_KEY_MAPPINGS (3U)
#define KEYS_CNT         (4U)

#define BLOCK_SIZE              (125U)
#define BLOCK_OFFSET            (18U)
#define SCREEN_WIDTH_BLOCK_CNT  (4U)
#define SCREEN_HEIGHT_BLOCK_CNT (4U)
#define SCREEN_WIDTH            (BLOCK_SIZE * SCREEN_WIDTH_BLOCK_CNT)
#define SCREEN_HEIGHT           (BLOCK_SIZE * SCREEN_HEIGHT_BLOCK_CNT)
#define FONT_SIZE               (32U)
#define TEXT_IN_BLOCK_OFFSET    (5U)



#endif /*CONFIG_H */