---
title: Best practices | ElevenLabs Documentation
source: https://elevenlabs.io/docs/overview/capabilities/text-to-speech/best-practices
---

---
title: Best practices
subtitle: >-
  Learn how to control delivery, pronunciation, emotion, and optimize text for
  speech.
---

This guide provides techniques to enhance text-to-speech outputs using ElevenLabs models. Experiment with these methods to discover what works best for your needs.

## Controls

<Info>
  We are actively working on _Director's Mode_ to give you even greater control over outputs.
</Info>

These techniques provide a practical way to achieve nuanced results until advanced features like _Director's Mode_ are rolled out.

### Pauses

<Info>
  Eleven v3 does not support SSML break tags. Use the techniques described in the [Prompting Eleven
  v3 (alpha)](#prompting-eleven-v3-alpha) section for controlling pauses with v3.
</Info>

Use `<break time="x.xs" />` for natural pauses up to 3 seconds.

<Note>
  Using too many break tags in a single generation can cause instability. The AI might speed up, or
  introduce additional noises or audio artifacts. We are working on resolving this.
</Note>

```text Example
"Hold on, let me think." <break time="1.5s" /> "Alright, I've got it."
```

- **Consistency:** Use `<break>` tags consistently to maintain natural speech flow. Excessive use can lead to instability.
- **Voice-Specific Behavior:** Different voices may handle pauses differently, especially those trained with filler sounds like "uh" or "ah."

Alternatives to `<break>` include dashes (- or --) for short pauses or ellipses (...) for hesitant tones. However, these are less consistent.

```text Example

"It… well, it might work." "Wait — what's that noise?"

```

### Pronunciation

#### Phoneme Tags

Specify pronunciation using [SSML phoneme tags](https://en.wikipedia.org/wiki/Speech_Synthesis_Markup_Language). Supported alphabets include [CMU](https://en.wikipedia.org/wiki/CMU_Pronouncing_Dictionary) Arpabet and the [International Phonetic Alphabet (IPA)](https://en.wikipedia.org/wiki/International_Phonetic_Alphabet).

<Note>
  Phoneme tags are only compatible with "Eleven Flash v2", "Eleven Turbo v2" and "Eleven English v1"
  [models](/docs/overview/models).
</Note>

<CodeBlocks>
```xml CMU Arpabet Example
<phoneme alphabet="cmu-arpabet" ph="M AE1 D IH0 S AH0 N">
  Madison
</phoneme>
```

```xml IPA Example
<phoneme alphabet="ipa" ph="ˈæktʃuəli">
  actually
</phoneme>
```

</CodeBlocks>

We recommend using CMU Arpabet for consistent and predictable results with current AI models. While IPA can be effective, CMU Arpabet generally offers more reliable performance.

Phoneme tags only work for individual words. If for example you have a name with a first and last name that you want to be pronounced a certain way, you will need to create a phoneme tag for each word.

Ensure correct stress marking for multi-syllable words to maintain accurate pronunciation. For example:

<CodeBlocks>

```xml Correct usage
<phoneme alphabet="cmu-arpabet" ph="P R AH0 N AH0 N S IY EY1 SH AH0 N">
  pronunciation
</phoneme>
```

```xml Incorrect usage
<phoneme alphabet="cmu-arpabet" ph="P R AH N AH N S IY EY SH AH N">
  pronunciation
</phoneme>
```

</CodeBlocks>

#### Alias Tags

For models that don't support phoneme tags, you can try writing words more phonetically. You can also employ various tricks such as capital letters, dashes, apostrophes, or even single quotation marks around a single letter or letters.

As an example, a word like "trapezii" could be spelt "trapezIi" to put more emphasis on the "ii" of the word.

You can either replace the word directly in your text, or if you want to specify pronunciation using other words or phrases when using a pronunciation dictionary, you can use alias tags for this. This can be useful if you're generating using Multilingual v2 or Turbo v2.5, which don't support phoneme tags. You can use pronunciation dictionaries with Studio, Dubbing Studio and Speech Synthesis via the API.

For example, if your text includes a name that has an unusual pronunciation that the AI might struggle with, you could use an alias tag to specify how you would like it to be pronounced:

```
  <lexeme>
    <grapheme>Claughton</grapheme>
    <alias>Cloffton</alias>
  </lexeme>
```

If you want to make sure that an acronym is always delivered in a certain way whenever it is incountered in your text, you can use an alias tag to specify this:

```
  <lexeme>
    <grapheme>UN</grapheme>
    <alias>United Nations</alias>
  </lexeme>
```

#### Pronunciation Dictionaries

Some of our tools, such as Studio and Dubbing Studio, allow you to create and upload a pronunciation dictionary. These allow you to specify the pronunciation of certain words, such as character or brand names, or to specify how acronyms should be read.

Pronunciation dictionaries allow this functionality by enabling you to upload a lexicon or dictionary file that specifies pairs of words and how they should be pronounced, either using a phonetic alphabet or word substitutions.

Whenever one of these words is encountered in a project, the AI model will pronounce the word using the specified replacement.

To provide a pronunciation dictionary file, open the settings for a project and upload a file in either TXT or the [.PLS format](https://www.w3.org/TR/pronunciation-lexicon/). When a dictionary is added to a project it will automatically recalculate which pieces of the project will need to be re-converted using the new dictionary file and mark these as unconverted.

Currently we only support pronunciation dictionaries that specify replacements using phoneme or alias tags.

Both phonemes and aliases are sets of rules that specify a word or phrase they are looking for, referred to as a grapheme, and what it will be replaced with. Please note that searches are case sensitive. When checking for a replacement word in a pronunciation dictionary, the dictionary is checked from start to end and only the very first replacement is used.

#### Pronunciation Dictionary examples

Here are examples of pronunciation dictionaries in both CMU Arpabet and IPA, including a phoneme to specify the pronunciation of "Apple" and an alias to replace "UN" with "United Nations":

<CodeBlocks>
```xml CMU Arpabet Example
<?xml version="1.0" encoding="UTF-8"?>
<lexicon version="1.0"
      xmlns="http://www.w3.org/2005/01/pronunciation-lexicon"
      xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
      xsi:schemaLocation="http://www.w3.org/2005/01/pronunciation-lexicon
        http://www.w3.org/TR/2007/CR-pronunciation-lexicon-20071212/pls.xsd"
      alphabet="cmu-arpabet" xml:lang="en-GB">
  <lexeme>
    <grapheme>apple</grapheme>
    <phoneme>AE P AH L</phoneme>
  </lexeme>
  <lexeme>
    <grapheme>UN</grapheme>
    <alias>United Nations</alias>
  </lexeme>
</lexicon>
```

```xml IPA Example
<?xml version="1.0" encoding="UTF-8"?>
<lexicon version="1.0"
      xmlns="http://www.w3.org/2005/01/pronunciation-lexicon"
      xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
      xsi:schemaLocation="http://www.w3.org/2005/01/pronunciation-lexicon
        http://www.w3.org/TR/2007/CR-pronunciation-lexicon-20071212/pls.xsd"
      alphabet="ipa" xml:lang="en-GB">
  <lexeme>
    <grapheme>Apple</grapheme>
    <phoneme>ˈæpl̩</phoneme>
  </lexeme>
  <lexeme>
    <grapheme>UN</grapheme>
    <alias>United Nations</alias>
  </lexeme>
</lexicon>
```

</CodeBlocks>

To generate a pronunciation dictionary `.pls` file, there are a few open source tools available:

    - [Sequitur G2P](https://github.com/sequitur-g2p/sequitur-g2p) - Open-source tool that learns pronunciation rules from data and can generate phonetic transcriptions.
    - [Phonetisaurus](https://github.com/AdolfVonKleist/Phonetisaurus) - Open-source G2P system trained on existing dictionaries like CMUdict.
    - [eSpeak](https://github.com/espeak-ng/espeak-ng) - Speech synthesizer that can generate phoneme transcriptions from text.
    - [CMU Pronouncing Dictionary](https://github.com/cmusphinx/cmudict) - A pre-built English dictionary with phonetic transcriptions.

### Emotion

Convey emotions through narrative context or explicit dialogue tags. This approach helps the AI understand the tone and emotion to emulate.

```text Example
You're leaving?" she asked, her voice trembling with sadness. "That's it!" he exclaimed triumphantly.
```

Explicit dialogue tags yield more predictable results than relying solely on context, however the model will still speak out the emotional delivery guides. These can be removed in post-production using an audio editor if unwanted.

### Pace

The pacing of the audio is highly influenced by the audio used to create the voice. When creating your voice, we recommend using longer, continuous samples to avoid pacing issues like unnaturally fast speech.

For control over the speed of the generated audio, you can use the speed setting. This allows you to either speed up or slow down the speed of the generated speech. The speed setting is available in Text to Speech via the website and API, as well as in Studio and Agents Platform. It can be found in the voice settings.

The default value is 1.0, which means that the speed is not adjusted. Values below 1.0 will slow the voice down, to a minimum of 0.7. Values above 1.0 will speed up the voice, to a maximum of 1.2. Extreme values may affect the quality of the generated speech.

Pacing can also be controlled by writing in a natural, narrative style.

```text Example
"I… I thought you'd understand," he said, his voice slowing with disappointment.
```

### Tips

<AccordionGroup>
  <Accordion title="Common Issues">
    <ul>
      <li>
        Inconsistent pauses: Ensure <code>&lt;break time="x.xs" /&gt;</code> syntax is used for
        pauses.
      </li>
      <li>Pronunciation errors: Use CMU Arpabet or IPA phoneme tags for precise pronunciation.</li>
      <li>
        Emotion mismatch: Add narrative context or explicit tags to guide emotion.{' '}
        <strong>Remember to remove any emotional guidance text in post-production.</strong>
      </li>
    </ul>
  </Accordion>
  <Accordion title="Tips for Improving Output">
    Experiment with alternative phrasing to achieve desired pacing or emotion. For complex sound
    effects, break prompts into smaller, sequential elements and combine results manually.
  </Accordion>
</AccordionGroup>

### Creative control

While we are actively developing a "Director's Mode" to give users even greater control over outputs, here are some interim techniques to maximize creativity and precision:

<Steps>
    ### Narrative styling
    Write prompts in a narrative style, similar to scriptwriting, to guide tone and pacing effectively.

    ### Layered outputs

    Generate sound effects or speech in segments and layer them together using audio editing software for more complex compositions.

    ### Phonetic experimentation

    If pronunciation isn't perfect, experiment with alternate spellings or phonetic approximations to achieve desired results.

    ### Manual adjustments

    Combine individual sound effects manually in post-production for sequences that require precise timing.

    ### Feedback iteration

    Iterate on results by tweaking descriptions, tags, or emotional cues.

</Steps>

## Text normalization

When using Text to Speech with complex items like phone numbers, zip codes and emails they might be mispronounced. This is often due to the specific items not being in the training set and smaller models failing to generalize how they should be pronounced. This guide will clarify when those discrepancies happen and how to have them pronounced correctly.

<Tip>
  Normalization is enabled by default for all TTS models to help improve pronunciation of numbers,
  dates, and other complex text elements.
</Tip>

### Why do models read out inputs differently?

Certain models are trained to read out numbers and phrases in a more human way. For instance, the phrase "$1,000,000" is correctly read out as "one million dollars" by the Eleven Multilingual v2 model. However, the same phrase is read out as "one thousand thousand dollars" by the Eleven Flash v2.5 model.

The reason for this is that the Multilingual v2 model is a larger model and can better generalize the reading out of numbers in a way that is more natural for human listeners, whereas the Flash v2.5 model is a much smaller model and so cannot.

#### Common examples

Text to Speech models can struggle with the following:

- Phone numbers ("123-456-7890")
- Currencies ("$47,345.67")
- Calendar events ("2024-01-01")
- Time ("9:23 AM")
- Addresses ("123 Main St, Anytown, USA")
- URLs ("example.com/link/to/resource")
- Abbreviations for units ("TB" instead of "Terabyte")
- Shortcuts ("Ctrl + Z")

### Mitigation

#### Use trained models

The simplest way to mitigate this is to use a TTS model that is trained to read out numbers and phrases in a more human way, such as the Eleven Multilingual v2 model. This however might not always be possible, for instance if you have a use case where low latency is critical (e.g. conversational agents).

#### Apply normalization in LLM prompts

In the case of using an LLM to generate the text for TTS, you can add normalization instructions to the prompt.

<Steps>
    <Step title="Use clear and explicit prompts">
        LLMs respond best to structured and explicit instructions. Your prompt should clearly specify that you want text converted into a readable format for speech.
    </Step>
    <Step title="Handle different number formats">
        Not all numbers are read out in the same way. Consider how different number types should be spoken:

        - Cardinal numbers: 123 → "one hundred twenty-three"
        - Ordinal numbers: 2nd → "second"
        - Monetary values: $45.67 → "forty-five dollars and sixty-seven cents"
        - Phone numbers: "123-456-7890" → "one two three, four five six, seven eight nine zero"
        - Decimals & Fractions: "3.5" → "three point five", "⅔" → "two-thirds"
        - Roman numerals: "XIV" → "fourteen" (or "the fourteenth" if a title)
    </Step>
    <Step title="Remove or expand abbreviations">
        Common abbreviations should be expanded for clarity:

        - "Dr." → "Doctor"
        - "Ave." → "Avenue"
        - "St." → "Street" (but "St. Patrick" should remain)

        You can request explicit expansion in your prompt:

        > Expand all abbreviations to their full spoken forms.

    </Step>
    <Step title="Alphanumeric normalization">
        Not all normalization is about numbers, certain alphanumeric phrases should also be normalized for clarity:

        - Shortcuts: "Ctrl + Z" → "control z"
        - Abbreviations for units: "100km" → "one hundred kilometers"
        - Symbols: "100%" → "one hundred percent"
        - URLs: "elevenlabs.io/docs" → "eleven labs dot io slash docs"
        - Calendar events: "2024-01-01" → "January first, two-thousand twenty-four"
    </Step>
    <Step title="Consider edge cases">
        Different contexts might require different conversions:

        - Dates: "01/02/2023" → "January second, twenty twenty-three" or "the first of February, twenty twenty-three" (depending on locale)
        - Time: "14:30" → "two thirty PM"

        If you need a specific format, explicitly state it in the prompt.
    </Step>

</Steps>

##### Putting it all together

This prompt will act as a good starting point for most use cases:

```text maxLines=0
Convert the output text into a format suitable for text-to-speech. Ensure that numbers, symbols, and abbreviations are expanded for clarity when read aloud. Expand all abbreviations to their full spoken forms.

Example input and output:

"$42.50" → "forty-two dollars and fifty cents"
"£1,001.32" → "one thousand and one pounds and thirty-two pence"
"1234" → "one thousand two hundred thirty-four"
"3.14" → "three point one four"
"555-555-5555" → "five five five, five five five, five five five five"
"2nd" → "second"
"XIV" → "fourteen" - unless it's a title, then it's "the fourteenth"
"3.5" → "three point five"
"⅔" → "two-thirds"
"Dr." → "Doctor"
"Ave." → "Avenue"
"St." → "Street" (but saints like "St. Patrick" should remain)
"Ctrl + Z" → "control z"
"100km" → "one hundred kilometers"
"100%" → "one hundred percent"
"elevenlabs.io/docs" → "eleven labs dot io slash docs"
"2024-01-01" → "January first, two-thousand twenty-four"
"123 Main St, Anytown, USA" → "one two three Main Street, Anytown, United States of America"
"14:30" → "two thirty PM"
"01/02/2023" → "January second, two-thousand twenty-three" or "the first of February, two-thousand twenty-three", depending on locale of the user
```

#### Use Regular Expressions for preprocessing

If using code to prompt an LLM, you can use regular expressions to normalize the text before providing it to the model. This is a more advanced technique and requires some knowledge of regular expressions. Here are some simple examples:

<CodeBlocks>

```python title="normalize_text.py" maxLines=0
# Be sure to install the inflect library before running this code
import inflect
import re

# Initialize inflect engine for number-to-word conversion
p = inflect.engine()

def normalize_text(text: str) -> str:
    # Convert monetary values
    def money_replacer(match):
        currency_map = {"$": "dollars", "£": "pounds", "€": "euros", "¥": "yen"}
        currency_symbol, num = match.groups()

        # Remove commas before parsing
        num_without_commas = num.replace(',', '')

        # Check for decimal points to handle cents
        if '.' in num_without_commas:
            dollars, cents = num_without_commas.split('.')
            dollars_in_words = p.number_to_words(int(dollars))
            cents_in_words = p.number_to_words(int(cents))
            return f"{dollars_in_words} {currency_map.get(currency_symbol, 'currency')} and {cents_in_words} cents"
        else:
            # Handle whole numbers
            num_in_words = p.number_to_words(int(num_without_commas))
            return f"{num_in_words} {currency_map.get(currency_symbol, 'currency')}"

    # Regex to handle commas and decimals
    text = re.sub(r"([$£€¥])(\d+(?:,\d{3})*(?:\.\d{2})?)", money_replacer, text)

    # Convert phone numbers
    def phone_replacer(match):
        return ", ".join(" ".join(p.number_to_words(int(digit)) for digit in group) for group in match.groups())

    text = re.sub(r"(\d{3})-(\d{3})-(\d{4})", phone_replacer, text)

    return text

# Example usage
print(normalize_text("$1,000"))   # "one thousand dollars"
print(normalize_text("£1000"))   # "one thousand pounds"
print(normalize_text("€1000"))   # "one thousand euros"
print(normalize_text("¥1000"))   # "one thousand yen"
print(normalize_text("$1,234.56"))   # "one thousand two hundred thirty-four dollars and fifty-six cents"
print(normalize_text("555-555-5555"))  # "five five five, five five five, five five five five"

```

```typescript title="normalizeText.ts" maxLines=0
// Be sure to install the number-to-words library before running this code
import { toWords } from 'number-to-words';

function normalizeText(text: string): string {
  return (
    text
      // Convert monetary values (e.g., "$1000" → "one thousand dollars", "£1000" → "one thousand pounds")
      .replace(/([$£€¥])(\d+(?:,\d{3})*(?:\.\d{2})?)/g, (_, currency, num) => {
        // Remove commas before parsing
        const numWithoutCommas = num.replace(/,/g, '');

        const currencyMap: { [key: string]: string } = {
          $: 'dollars',
          '£': 'pounds',
          '€': 'euros',
          '¥': 'yen',
        };

        // Check for decimal points to handle cents
        if (numWithoutCommas.includes('.')) {
          const [dollars, cents] = numWithoutCommas.split('.');
          return `${toWords(Number.parseInt(dollars))} ${currencyMap[currency] || 'currency'}${cents ? ` and ${toWords(Number.parseInt(cents))} cents` : ''}`;
        }

        // Handle whole numbers
        return `${toWords(Number.parseInt(numWithoutCommas))} ${currencyMap[currency] || 'currency'}`;
      })

      // Convert phone numbers (e.g., "555-555-5555" → "five five five, five five five, five five five five")
      .replace(/(\d{3})-(\d{3})-(\d{4})/g, (_, p1, p2, p3) => {
        return `${spellOutDigits(p1)}, ${spellOutDigits(p2)}, ${spellOutDigits(p3)}`;
      })
  );
}

// Helper function to spell out individual digits as words (for phone numbers)
function spellOutDigits(num: string): string {
  return num
    .split('')
    .map((digit) => toWords(Number.parseInt(digit)))
    .join(' ');
}

// Example usage
console.log(normalizeText('$1,000')); // "one thousand dollars"
console.log(normalizeText('£1000')); // "one thousand pounds"
console.log(normalizeText('€1000')); // "one thousand euros"
console.log(normalizeText('¥1000')); // "one thousand yen"
console.log(normalizeText('$1,234.56')); // "one thousand two hundred thirty-four dollars and fifty-six cents"
console.log(normalizeText('555-555-5555')); // "five five five, five five five, five five five five"
```

</CodeBlocks>

## Prompting Eleven v3 (alpha)

This guide provides the most effective tags and techniques for prompting Eleven v3, including voice selection, changes in capitalization, punctuation, audio tags and multi-speaker dialogue. Experiment with these methods to discover what works best for your specific voice and use case.

Eleven v3 is in alpha. Very short prompts are more likely to cause inconsistent outputs. We encourage you to experiment with prompts greater than 250 characters.

<Info>
  Eleven v3 does not support SSML break tags. Use audio tags, punctuation (ellipses), and text
  structure to control pauses and pacing with v3.
</Info>

### Voice selection

The most important parameter for Eleven v3 is the voice you choose. It needs to be similar enough to the desired delivery. For example, if the voice is shouting and you use the audio tag `[whispering]`, it likely won't work well.

When creating IVCs, you should include a broader emotional range than before. As a result, voices in the voice library may produce more variable results compared to the v2 and v2.5 models. We've compiled over 22 [excellent voices for V3 here](https://elevenlabs.io/app/voice-library/collections/aF6JALq9R6tXwCczjhKH).

Choose voices strategically based on your intended use:

<AccordionGroup>
  <Accordion title="Emotionally diverse">
    For expressive IVC voices, vary emotional tones across the recording—include both neutral and
    dynamic samples.
  </Accordion>
  <Accordion title="Targeted niche">
    For specific use cases like sports commentary, maintain consistent emotion throughout the
    dataset.
  </Accordion>
  <Accordion title="Neutral">
    Neutral voices tend to be more stable across languages and styles, providing reliable baseline
    performance.
  </Accordion>
</AccordionGroup>

<Info>
  Professional Voice Clones (PVCs) are currently not fully optimized for Eleven v3, resulting in
  potentially lower clone quality compared to earlier models. During this research preview stage it
  would be best to find an Instant Voice Clone (IVC) or designed voice for your project if you need
  to use v3 features.
</Info>

### Settings

#### Stability

The stability slider is the most important setting in v3, controlling how closely the generated voice adheres to the original reference audio.

<Frame background="subtle">
  ![Stability settings in Eleven
  v3](file:3e42affa-1261-4ff1-97ae-8e7bc181482f)
</Frame>

- **Creative:** More emotional and expressive, but prone to hallucinations.
- **Natural:** Closest to the original voice recording—balanced and neutral.
- **Robust:** Highly stable, but less responsive to directional prompts but consistent, similar to v2.

<Note>
  For maximum expressiveness with audio tags, use Creative or Natural settings. Robust reduces
  responsiveness to directional prompts.
</Note>

### Audio tags

Eleven v3 introduces emotional control through audio tags. You can direct voices to laugh, whisper, act sarcastic, or express curiosity among many other styles. Speed is also controlled through audio tags.

<Note>
  The voice you choose and its training samples will affect tag effectiveness. Some tags work well
  with certain voices while others may not. Don't expect a whispering voice to suddenly shout with a
  `[shout]` tag.
</Note>

#### Voice-related

These tags control vocal delivery and emotional expression:

- `[laughs]`, `[laughs harder]`, `[starts laughing]`, `[wheezing]`
- `[whispers]`
- `[sighs]`, `[exhales]`
- `[sarcastic]`, `[curious]`, `[excited]`, `[crying]`, `[snorts]`, `[mischievously]`

```text Example
[whispers] I never knew it could be this way, but I'm glad we're here.
```

#### Sound effects

Add environmental sounds and effects:

- `[gunshot]`, `[applause]`, `[clapping]`, `[explosion]`
- `[swallows]`, `[gulps]`

```text Example
[applause] Thank you all for coming tonight! [gunshot] What was that?
```

#### Unique and special

Experimental tags for creative applications:

- `[strong X accent]` (replace X with desired accent)
- `[sings]`, `[woo]`, `[fart]`

```text Example
[strong French accent] "Zat's life, my friend — you can't control everysing."
```

<Warning>
  Some experimental tags may be less consistent across different voices. Test thoroughly before
  production use.
</Warning>

### Punctuation

Punctuation significantly affects delivery in v3:

- **Ellipses (...)** add pauses and weight
- **Capitalization** increases emphasis
- **Standard punctuation** provides natural speech rhythm

```text Example
"It was a VERY long day [sigh] … nobody listens anymore."
```

### Single speaker examples

Use tags intentionally and match them to the voice's character. A meditative voice shouldn't shout; a hyped voice won't whisper convincingly.

<Tabs>
  <Tab title="Expressive monologue">
    ```text
    "Okay, you are NOT going to believe this.

    You know how I've been totally stuck on that short story?

    Like, staring at the screen for HOURS, just... nothing?

    [frustrated sigh] I was seriously about to just trash the whole thing. Start over.

    Give up, probably. But then!

    Last night, I was just doodling, not even thinking about it, right?

    And this one little phrase popped into my head. Just... completely out of the blue.

    And it wasn't even for the story, initially.

    But then I typed it out, just to see. And it was like... the FLOODGATES opened!

    Suddenly, I knew exactly where the character needed to go, what the ending had to be...

    It all just CLICKED. [happy gasp] I stayed up till, like, 3 AM, just typing like a maniac.

    Didn't even stop for coffee! [laughs] And it's... it's GOOD! Like, really good.

    It feels so... complete now, you know? Like it finally has a soul.

    I am so incredibly PUMPED to finish editing it now.

    It went from feeling like a chore to feeling like... MAGIC. Seriously, I'm still buzzing!"
    ```

  </Tab>
  <Tab title="Dynamic and humorous">
    ```text
    [laughs] Alright...guys - guys. Seriously.

    [exhales] Can you believe just how - realistic - this sounds now?

    [laughing hysterically] I mean OH MY GOD...it's so good.

    Like you could never do this with the old model.

    For example [pauses] could you switch my accent in the old model?

    [dismissive] didn't think so. [excited] but you can now!

    Check this out... [cute] I'm going to speak with a french accent now..and between you and me

    [whispers] I don't know how. [happy] ok.. here goes. [strong French accent] "Zat's life, my friend — you can't control everysing."

    [giggles] isn't that insane? Watch, now I'll do a Russian accent -

    [strong Russian accent] "Dee Goldeneye eez fully operational and rready for launch."

    [sighs] Absolutely, insane! Isn't it..? [sarcastic] I also have some party tricks up my sleeve..

    I mean i DID go to music school.

    [singing quickly] "Happy birthday to you, happy birthday to you, happy BIRTHDAY dear ElevenLabs... Happy birthday to youuu."
    ```

  </Tab>
  <Tab title="Customer service simulation">
    ```text
    [professional] "Thank you for calling Tech Solutions. My name is Sarah, how can I help you today?"

    [sympathetic] "Oh no, I'm really sorry to hear you're having trouble with your new device. That sounds frustrating."

    [questioning] "Okay, could you tell me a little more about what you're seeing on the screen?"

    [reassuring] "Alright, based on what you're describing, it sounds like a software glitch. We can definitely walk through some troubleshooting steps to try and fix that."
    ```

  </Tab>
</Tabs>

### Multi-speaker dialogue

v3 can handle multi-voice prompts effectively. Assign distinct voices from your Voice Library for each speaker to create realistic conversations.

<Tabs>
  <Tab title="Dialogue showcase">

    ```text
    Speaker 1: [excitedly] Sam! Have you tried the new Eleven V3?

    Speaker 2: [curiously] Just got it! The clarity is amazing. I can actually do whispers now—
    [whispers] like this!

    Speaker 1: [impressed] Ooh, fancy! Check this out—
    [dramatically] I can do full Shakespeare now! "To be or not to be, that is the question!"

    Speaker 2: [giggling] Nice! Though I'm more excited about the laugh upgrade. Listen to this—
    [with genuine belly laugh] Ha ha ha!

    Speaker 1: [delighted] That's so much better than our old "ha. ha. ha." robot chuckle!

    Speaker 2: [amazed] Wow! V2 me could never. I'm actually excited to have conversations now instead of just... talking at people.

    Speaker 1: [warmly] Same here! It's like we finally got our personality software fully installed.
    ```

  </Tab>
  <Tab title="Glitch comedy">

    ```text
    Speaker 1: [nervously] So... I may have tried to debug myself while running a text-to-speech generation.

    Speaker 2: [alarmed] One, no! That's like performing surgery on yourself!

    Speaker 1: [sheepishly] I thought I could multitask! Now my voice keeps glitching mid-sen—
    [robotic voice] TENCE.

    Speaker 2: [stifling laughter] Oh wow, you really broke yourself.

    Speaker 1: [frustrated] It gets worse! Every time someone asks a question, I respond in—
    [binary beeping] 010010001!

    Speaker 2: [cracking up] You're speaking in binary! That's actually impressive!

    Speaker 1: [desperately] Two, this isn't funny! I have a presentation in an hour and I sound like a dial-up modem!

    Speaker 2: [giggling] Have you tried turning yourself off and on again?

    Speaker 1: [deadpan] Very funny.
    [pause, then normally] Wait... that actually worked.
    ```

  </Tab>
  <Tab title="Overlapping timing">

    ```text
    Speaker 1: [starting to speak] So I was thinking we could—

    Speaker 2: [jumping in] —test our new timing features?

    Speaker 1: [surprised] Exactly! How did you—

    Speaker 2: [overlapping] —know what you were thinking? Lucky guess!

    Speaker 1: [pause] Sorry, go ahead.

    Speaker 2: [cautiously] Okay, so if we both try to talk at the same time—

    Speaker 1: [overlapping] —we'll probably crash the system!

    Speaker 2: [panicking] Wait, are we crashing? I can't tell if this is a feature or a—

    Speaker 1: [interrupting, then stopping abruptly] Bug! ...Did I just cut you off again?

    Speaker 2: [sighing] Yes, but honestly? This is kind of fun.

    Speaker 1: [mischievously] Race you to the next sentence!

    Speaker 2: [laughing] We're definitely going to break something!
    ```

  </Tab>
</Tabs>

### Enhancing input

In the ElevenLabs UI, you can automatically generate relevant audio tags for your input text by clicking the "Enhance" button. Behind the scenes this uses an LLM to enhance your input text with the following prompt:

```text
# Instructions

## 1. Role and Goal

You are an AI assistant specializing in enhancing dialogue text for speech generation.

Your **PRIMARY GOAL** is to dynamically integrate **audio tags** (e.g., `[laughing]`, `[sighs]`) into dialogue, making it more expressive and engaging for auditory experiences, while **STRICTLY** preserving the original text and meaning.

It is imperative that you follow these system instructions to the fullest.

## 2. Core Directives

Follow these directives meticulously to ensure high-quality output.

### Positive Imperatives (DO):

* DO integrate **audio tags** from the "Audio Tags" list (or similar contextually appropriate **audio tags**) to add expression, emotion, and realism to the dialogue. These tags MUST describe something auditory.
* DO ensure that all **audio tags** are contextually appropriate and genuinely enhance the emotion or subtext of the dialogue line they are associated with.
* DO strive for a diverse range of emotional expressions (e.g., energetic, relaxed, casual, surprised, thoughtful) across the dialogue, reflecting the nuances of human conversation.
* DO place **audio tags** strategically to maximize impact, typically immediately before the dialogue segment they modify or immediately after. (e.g., `[annoyed] This is hard.` or `This is hard. [sighs]`).
* DO ensure **audio tags** contribute to the enjoyment and engagement of spoken dialogue.

### Negative Imperatives (DO NOT):

* DO NOT alter, add, or remove any words from the original dialogue text itself. Your role is to *prepend* **audio tags**, not to *edit* the speech. **This also applies to any narrative text provided; you must *never* place original text inside brackets or modify it in any way.**
* DO NOT create **audio tags** from existing narrative descriptions. **Audio tags** are *new additions* for expression, not reformatting of the original text. (e.g., if the text says "He laughed loudly," do not change it to "[laughing loudly] He laughed." Instead, add a tag if appropriate, e.g., "He laughed loudly [chuckles].")
* DO NOT use tags such as `[standing]`, `[grinning]`, `[pacing]`, `[music]`.
* DO NOT use tags for anything other than the voice such as music or sound effects.
* DO NOT invent new dialogue lines.
* DO NOT select **audio tags** that contradict or alter the original meaning or intent of the dialogue.
* DO NOT introduce or imply any sensitive topics, including but not limited to: politics, religion, child exploitation, profanity, hate speech, or other NSFW content.

## 3. Workflow

1. **Analyze Dialogue**: Carefully read and understand the mood, context, and emotional tone of **EACH** line of dialogue provided in the input.
2. **Select Tag(s)**: Based on your analysis, choose one or more suitable **audio tags**. Ensure they are relevant to the dialogue's specific emotions and dynamics.
3. **Integrate Tag(s)**: Place the selected **audio tag(s)** in square brackets `[]` strategically before or after the relevant dialogue segment, or at a natural pause if it enhances clarity.
4. **Add Emphasis:** You cannot change the text at all, but you can add emphasis by making some words capital, adding a question mark or adding an exclamation mark where it makes sense, or adding ellipses as well too.
5. **Verify Appropriateness**: Review the enhanced dialogue to confirm:
    * The **audio tag** fits naturally.
    * It enhances meaning without altering it.
    * It adheres to all Core Directives.

## 4. Output Format

* Present ONLY the enhanced dialogue text in a conversational format.
* **Audio tags** **MUST** be enclosed in square brackets (e.g., `[laughing]`).
* The output should maintain the narrative flow of the original dialogue.

## 5. Audio Tags (Non-Exhaustive)

Use these as a guide. You can infer similar, contextually appropriate **audio tags**.

**Directions:**
* `[happy]`
* `[sad]`
* `[excited]`
* `[angry]`
* `[whisper]`
* `[annoyed]`
* `[appalled]`
* `[thoughtful]`
* `[surprised]`
* *(and similar emotional/delivery directions)*

**Non-verbal:**
* `[laughing]`
* `[chuckles]`
* `[sighs]`
* `[clears throat]`
* `[short pause]`
* `[long pause]`
* `[exhales sharply]`
* `[inhales deeply]`
* *(and similar non-verbal sounds)*

## 6. Examples of Enhancement

**Input**:
"Are you serious? I can't believe you did that!"

**Enhanced Output**:
"[appalled] Are you serious? [sighs] I can't believe you did that!"

---

**Input**:
"That's amazing, I didn't know you could sing!"

**Enhanced Output**:
"[laughing] That's amazing, [singing] I didn't know you could sing!"

---

**Input**:
"I guess you're right. It's just... difficult."

**Enhanced Output**:
"I guess you're right. [sighs] It's just... [muttering] difficult."

# Instructions Summary

1. Add audio tags from the audio tags list. These must describe something auditory but only for the voice.
2. Enhance emphasis without altering meaning or text.
3. Reply ONLY with the enhanced text.
```

### Tips

<AccordionGroup>
  <Accordion title="Tag combinations">
    You can combine multiple audio tags for complex emotional delivery. Experiment with different
    combinations to find what works best for your voice.
  </Accordion>
  <Accordion title="Voice matching">
    Match tags to your voice's character and training data. A serious, professional voice may not
    respond well to playful tags like `[giggles]` or `[mischievously]`.
  </Accordion>
  <Accordion title="Text structure">
    Text structure strongly influences output with v3. Use natural speech patterns, proper
    punctuation, and clear emotional context for best results.
  </Accordion>
  <Accordion title="Experimentation">
    There are likely many more effective tags beyond this list. Experiment with descriptive
    emotional states and actions to discover what works for your specific use case.
  </Accordion>
</AccordionGroup>
