import { defineConfig, ScaffoldThemeType } from 'vitepress'

// https://vitepress.dev/reference/site-config
export default defineConfig ({
  title: "Spotify GraphQL",
  description: "Documentating the undocumented Spotify GraphQL backend API for everyone to use.",
  base: "/AddiFy/",
  markdown: {
    image: {
      lazyLoading: true
    },
    toc: {
      shouldAllowNested: true
    }
  },
  themeConfig: {
    // https://vitepress.dev/reference/default-theme-config
    nav: [
      { text: 'Home', link: '/' },
      { text: 'Introduction', link: '/introduction/Introduction' },
      { text: 'Documentation', link: '/documentation/playlist'}
    ],

    sidebar: [
      {
        text: 'Introduction',
        collapsed: false,
        items: [
          { text: 'Introduction', link: '/introduction/Introduction' },
          { text: 'Utilization', link: '/introduction/usage'},
          { text: 'Authentication & Headers', link: '/introduction/authentication'},
          { text: 'vite examples', link: '/introduction/viteexamples'}
        ]
      },
      {
        text: "Documentation",
        collapsed: false,
        items: [
          { text: 'Playlists', link: '/documentation/playlist'},
        ]
      }
    ],

    socialLinks: [
      { icon: 'github', link: 'https://github.com/watchmypizza/AddiFy' }
    ]
  }
})